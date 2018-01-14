#include<ilcplex\ilocplex.h>
#include"Util.h	"
#include"Cost.h"
#include<vector>
using namespace std;


int main() {
	//Input
	vector<WareHouse>*warehouses= InputWH();
	vector<Factory>* factories=InputFac();
	vector<Customer>* customers=InputCus();

	//Allocate Demand
	 AllocateCustomerDemand((*customers), (*warehouses));
	 AllocateWarehouseDemand((*warehouses), (*factories));

	 //�жϵ�ǰ����������Ƿ�������ֿ�
	 setSetable((*warehouses));

	 //���߱���
	 vector<pair<Factory, bool>> newfacs=NewFactory((*factories));
	 vector<pair<WareHouse, bool>> newwhs=NewWarehouse((*warehouses));
	
	 int fv_size(newfacs.size());
	 int wv_size(newwhs.size());

	 //����ģ��
	IloEnv env;

	try {
		IloModel model(env);
		
		//��������
		IloNumVarArray fvars(env);
		IloNumVarArray wvars(env);

		for(int i=0;i<fv_size;++i)
			fvars.add(IloNumVar(env, ILOBOOL));

		for (int i = 0; i<wv_size; ++i)
			wvars.add(IloNumVar(env, ILOBOOL));

		model.add(fvars);
		model.add(wvars);

		//Ŀ�꺯��

		IloExpr expr(env);
		for(int i=0;i<4;++i)
			expr +=(*factories)[i].getD()*(*factories)[i].getPf();//�ɳ��������ɱ�

		for(int i=0;i<fv_size;++i)
			expr += newfacs[i].first.getD()*newfacs[i].first.getPf()*fvars[i]+fvars[i]*4000000;//�³��������ɱ�+���ܵĹ̶��ɱ�
		
		for (int i = 0; i < 22; ++i)
			expr += OperationCost((*warehouses)[i]);//�ɲֿ������ɱ�
		
		for (int i = 0; i < wv_size; ++i)
			expr += OperationCost(newwhs[i].first)*wvars[i];//�²ֿ������ɱ�

		for (int i = 0; i < warehouses->size(); ++i)
			expr += StorageCost((*warehouses)[i]);//�洢�ɱ�

		for (int i = 0; i < customers->size(); ++i)
			expr += (*customers)[i].getTotalTranportCost();//�˷�
		
		for (int i = 0; i < 22; ++i)//�˷�
			expr += (*warehouses)[i].getTMf();

		for (int i = 0; i < wv_size; ++i)//�˷�
			expr += newwhs[i].first.getTMf()*wvars[i];


		IloObjective obj(env, expr, IloObjective::Minimize);//Ŀ�꺯��

		//Լ������
		IloExpr c(env);
		
		int total_demand(0);
		for (int i = 0; i < customers->size(); ++i)
			total_demand += (*customers)[i].getD();//����
	
		for (int i = 0; i < (factories->size() - newfacs.size()); ++i)
			c += (*factories)[i].getP();
		for (int i = 0; i <  newfacs.size(); ++i)
			c += newfacs[i].first.getP()*fvars[i];//����

		model.add(c > total_demand);

		for (int i = 0; i < newwhs.size(); ++i) {
			IloRange  ctemp(env, 0, newwhs[i].first.Y() - wvars[i], 1);
			model.add(ctemp);
		}//��ͽ���������
		
		
		
		//��ģ�������
		IloCplex cplex(model);
		if (!cplex.solve()) {
			env.error() << "Failed to optimize LP." << endl;
			throw(-1);
		}
		IloNumArray vals(env);
		env.out() << "Solution status = " << cplex.getStatus() << endl;
		env.out() << "Solution value = " << cplex.getObjValue() << endl;
		//cplex.getValues(vals, vars);
		env.out() << "Values = " << vals << endl;
	}
	catch (IloException& e) {
		cerr << "Concert exception caught: " << e << endl;
	}
	catch (...) {
		cerr << "Unknown exception caught" << endl;
	}
	system("pause");
}
