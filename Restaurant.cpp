#include "main.h"
extern int MAXSIZE;

class imp_res : public Restaurant
{
public:
	imp_res() {};
	class DLinkedList {
	public:
		customer* head;
		customer* curr;
		customer* latest;
		int cnt;
		// Constructors
		DLinkedList() {
			head = nullptr;
			cnt = 0;
		};
		void insertFirst(customer* it)
		{
			customer* tmp = head->prev;
			head->prev->next = it;
			head->next->prev = it;
			cnt++;
			latest = it;
		}
		void insertAfter(customer* it) {
			customer* tmp = curr->next;
			it->next = curr->next;
			curr->next = it;
			it->prev = curr;
			tmp->prev = it;
			cnt++;
			curr = it;
			delete tmp;
		}
		void insertBefore(customer* it) {
			customer* tmp = curr->prev;
			curr->prev = it;
			it->prev = curr->prev->prev;
			tmp->next = it;
			it->next = curr;
			cnt++;
			curr = it;
			delete tmp;
		}
		bool isEmpty() {
			return head == nullptr;
		}
		int size() { return cnt; }
		void cusDel(customer* it) {
			it->next->prev = it->prev;
			it->prev->next = it->next;
			delete it;
			cnt--;
		}
		bool sameName(DLinkedList list, customer* it)
		{
			customer* tmp = list.head;
			for (int i = 0; i < cnt; i++)
			{
				if (it->name == tmp->name) return 1;
			}
			return 0;
		}
		void allDel() {
			customer* tmp = head;
			for (int i = 0; i < cnt; i++)
			{
				delete tmp;
				tmp = tmp->next;
			}
		}
		customer* cusFind(customer* x)
		{
			customer* tmp = head;
			for (int i = 0; i < cnt; i++)
			{
				if (tmp == x) return tmp;
				tmp = tmp->next;
			}
			return tmp;
		}
	};
	DLinkedList table;
	DLinkedList waitList;
	DLinkedList order;

	void RED(string name, int energy)
	{
		cout << name << " " << energy << endl;
		customer* cus = new customer(name, energy, nullptr, nullptr);

		// Chi nhan khach co energy >0 hoac energy <0
		if (cus->energy > 0 || cus->energy < 0)
		{
			bool sameName = order.sameName(order, cus);
			if (!sameName) {
				order.insertAfter(cus);
				//neu moi mo cua thi ngoi dau cung duoc
				if (table.isEmpty()) {
					table.insertFirst(cus);
					order.insertFirst(cus);
				}
				else
				{
					if (table.size() < MAXSIZE / 2)
					{
						int latestE = table.latest->energy;
						if (cus->energy >= latestE) table.insertAfter(cus);
						else table.insertBefore(cus);
						order.insertAfter(cus);
					}
					else
					{
						if (table.size() >= MAXSIZE / 2 && table.size() <= MAXSIZE)
						{
							customer* tmp = table.head;
							customer* max = tmp;
							while (tmp != table.head->prev)
							{
								if (abs(tmp->energy - cus->energy) > abs(max->energy - cus->energy)) max = tmp;
								tmp = tmp->next;
							}
							int RES = max->energy - cus->energy;
							if (RES > 0) table.insertAfter(cus);
							else table.insertBefore(cus);
							order.insertAfter(cus);
						}
						if (table.size() > MAXSIZE && waitList.size() < MAXSIZE)
						{
							waitList.insertAfter(cus);
						}
					}
				}
			}
		}
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
		if (num <= 0) return;
		if (num >= table.size() || num > MAXSIZE) table.allDel();
		else {
			for (int i = 0; i < num; i++)
			{
				customer* tmp = order.head;
				customer* del = table.cusFind(tmp);
				table.cusDel(del);
			}
		}
		if (waitList.size() != 0) {
			customer* tmp = waitList.head;
			RED(tmp->name, tmp->energy);
			waitList.cusDel(tmp);
		}
	}
	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
		int posSum = 0;
		int posCnt = 0;
		int negSum = 0;
		int negCnt = 0;
		customer* tabletmp = table.head;
		customer* waittmp = waitList.head;
		for (int i = 0; i < table.size();)
		{
			if (tabletmp->energy > 0)
			{
				posSum += tabletmp->energy;
				posCnt++;
			}
			else
			{
				negSum -= tabletmp->energy;
				negCnt++;
			}
			tabletmp = tabletmp->next;
		}
		for (int i = 0; i < waitList.size();)
		{
			if (waittmp->energy > 0) posSum++;
			else negSum--;
			waittmp = waittmp->next;
		}
		// Duoi het cac oan linh dang co mat tai nha hang
		if (posSum >= negSum)
		{
			int i = 0;
			customer* tmp = order.head;
			for (int i = 0; i < order.size();)
			{
				tmp = tmp->next;
			}
			// in ra man hinh
			while (i < negCnt)
			{
				if (tmp->energy < 0)
				{
					cout << tmp->name << "-" << tmp->energy << endl;
					order.cusDel(tmp);
					i++;
				}
				tmp = tmp->prev;
			}

			//xoa khoi ban
			int j = 0;
			customer* tmptab = table.head;
			while (j < negCnt)
			{
				if (tmptab->energy < 0)
				{
					table.cusDel(tmptab);
					j++;
				}
				tmptab = tmptab->next;
			}
			int k = 0;
			customer* tmpwait = waitList.head;
			while (k < negCnt)
			{
				if (tmpwait->energy < 0)
				{
					waitList.cusDel(tmpwait);
					k++;
				}
				tmpwait = tmpwait->next;
			}
		}
	}
	void LIGHT(int num)
	{
		cout << "light " << num << endl;
		if (num == 0)
		{
			customer* tmp = waitList.head;
			for (int i = 0; i < waitList.size();)
			{
				cout << tmp->name << "-" << tmp->energy << endl;
				tmp = tmp->next;
			}
		}
		else
		{
			if (num < 0)
			{
				customer* tmp = table.curr;
				customer* tmp2 = table.curr->next;
				while (tmp != tmp2)
				{
					cout << tmp->name << "-" << tmp->energy << endl;
					tmp = tmp->prev;
				}
			}
			else
			{
				customer* tmp = table.curr;
				customer* tmp2 = table.curr->prev;
				while (tmp != tmp2)
				{
					cout << tmp->name << "-" << tmp->energy << endl;
					tmp = tmp->next;
				}
			}
		}
	}
};