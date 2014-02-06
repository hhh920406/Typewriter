package com.book.recorder;

import java.util.Date;
import java.util.Vector;

public class AccountDataSet {
	public Vector<AccountData> list = new Vector<AccountData>();
	
	int len() {
		return list.size();
	}
	
	AccountData get(int index) {
		return list.elementAt(index);
	}
	
	void add(AccountData node) {
		if (node.id == 0) {
			Date date = new Date();
			node.id = date.getTime();
		}
		list.add(node);
		sort();
	}
	
	void remove(long id) {
		for (int i = 0; i < len(); ++i) {
			if (get(i).id == id) {
				list.remove(i);
				break;
			}
		}
	}
	
	void sort() {
		for (int i = 0; i < len(); ++i) {
			for (int j = 0; j < len(); ++j) {
				if (get(i).isBigger(get(j))) {
					AccountData temp = get(i);
					list.setElementAt(get(j), i);
					list.setElementAt(temp, j);
				}
			}
		}
	}
	
	float totalIncome() {
		float res = 0.0f;
		for (int i = 0; i < len(); ++i) {
			if (get(i).isIncome) {
				res += get(i).amount;
			}
		}
		return res;
	}
	
	float totalOutcome() {
		float res = 0.0f;
		for (int i = 0; i < len(); ++i) {
			if (!get(i).isIncome) {
				res += get(i).amount;
			}
		}
		return res;
	}
		
	float total() {
		return totalIncome() - totalOutcome();
	}
}
