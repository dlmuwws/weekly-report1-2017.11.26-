#pragma once

template<typename Type> class Element {
public:
	Type GetKey() {
		return key;
	}

	void SetKey(Type item) {
		key = item;
	}

public:
	Element<Type>& operator =(Element<Type> copy) {
		key = copy.key;
		return *this;
	}

	bool operator ==(Element<Type> item) {
		return this->key == item.key;
	}

	bool operator !=(Element<Type> item) {
		return this->key != item.key;
	}

	bool operator <(Element<Type> item) {
		return this->key < item.key;
	}

	bool operator >(Element<Type> item) {
		return this->key > item.key;
	}

	bool operator >=(Element<Type> item) {
		return this->key >= item.key;
	}

	bool operator <=(Element<Type> item) {
		return this->key <= item.key;
	}


private:
	Type key;
};
