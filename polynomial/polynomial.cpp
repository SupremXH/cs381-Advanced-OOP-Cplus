#include<iostream>
#include<fstream>
#include<ostream>
#include<regex>
using namespace std;
class poly {
public:
	class node {
	public:
		int coef;
		int exp;
		node* next;
		node(int coef, int exp) {
			this->coef = coef;
			this->exp = exp;
		}
	};
	node* head=new node(0,0);
	node* gethead() {
		return head;
	}
	void canonical(node* head,string val) {
		regex e(R"([-+]?((\d*[xX]\^[+-]?\d+)|(\d*[xX])|(\d+)))");
		sregex_token_iterator first(val.begin(), val.end(), e), last;
		while (first != last) {
			string token= *first++;
			smatch sm;
			if (regex_match(token, sm, regex(R"(([+-]?\d*)([xX](\^([+-]?\d+))?)?)"))) {
				int coef;
				if (sm[1].str().empty()) {
					coef = 1;
				}
				else if (sm[1].str() == "-" || sm[1].str() == "+") {
					coef = stoi(sm[1].str() + "1");
				}
				else {
					coef = stoi(sm[1]);
				}
				int exp;
				if (!sm[2].str().empty()) {
					if (!sm[4].str().empty()) {
						exp = stoi(sm[4].str());
					}
					else {
						exp = 1;
					}
				}
				else {
					exp = 0;
				}
				//cout<<coef<<" "<<exp<< endl;
				node* newNode = new node(coef, exp);
				nodeInsert(head,newNode);
			}
		}
	}
	void nodeInsert(node* head,node* newnode) {
		node* cur = head;
		while (cur->next != NULL) {
			if (cur->next->exp < newnode->exp) break;
			if (cur->next->exp == newnode->exp) {
				int newCoef = cur->next->coef + newnode->coef;
				node* n = new node(newCoef, newnode->exp);
				n->next = cur->next->next;
				cur->next = n;
				return;
			}
				cur = cur->next;
		}
		newnode->next = cur->next;
		cur->next = newnode;
	}
	void print(node* head,ofstream& outfile) {
		node* cur = head;
		while (cur->next != NULL) {
			if (cur == head && cur->next->coef == 1) outfile<<"";
			else if (cur->next->coef == -1 && cur->next->exp!=0) outfile<< "-";
			else if (cur->next->coef == 1) outfile<< "+";
			else if (cur->next->coef > 1) outfile<< "+"<<cur->next->coef;
			else outfile<< cur->next->coef;
			if (cur->next->exp == 1) outfile<< "x";
			else if (cur->next->exp > 1) outfile<< "x^" << cur->next->exp;
			cur = cur->next;
		}
		outfile<< endl;
	}
	void findsum(node* head,node* head1, node* head2) {
		node* cur = head1;
		while (cur->next != NULL) {
			nodeInsert(head,new node(cur->next->coef, cur->next->exp));
			cur = cur->next;
		}
		cur = head2;
		while (cur->next != NULL) {
			nodeInsert(head, new node(cur->next->coef, cur->next->exp));
			cur = cur->next;
		}
	}
	void finddiff(node* head, node* head1, node* head2) {
		node* cur = head1;
		while (cur->next != NULL) {
			nodeInsert(head, new node(cur->next->coef, cur->next->exp));
			cur = cur->next;
		}
		cur = head2;
		while (cur->next != NULL) {
			nodeInsert(head, new node(-cur->next->coef, cur->next->exp));
			cur = cur->next;
		}
	}
	void findprod(node* head, node* head1, node* head2) {
		node* cur = head1;
		while (cur->next != NULL) {
		node* cur1 = head2;
			while (cur1->next != NULL) {
				nodeInsert(head, new node(cur->next->coef*cur1->next->coef,cur->next->exp+cur1->next->exp));
				cur1 = cur1->next;
			}
			cur = cur->next;
		}
		
		
	}
	void construct(ifstream& infile, ofstream& outfile) {
		string val,val2;
		while (infile >> val && infile >> val2) {
			poly* p1 = new poly();
			canonical(p1->gethead(), val);
			outfile<< "the canonical form of p1 is:\n";
			print(p1->gethead(), outfile);
			poly* p2 = new poly();
			canonical(p2->gethead(), val2);
			outfile<< "the canonical form of p2 is:\n";
			print(p2->gethead(), outfile);
			poly* sum = new poly();
			findsum(sum->gethead(), p1->gethead(), p2->gethead());
			outfile<< "the sum of p1 and p2 is:\n";
			print(sum->gethead(), outfile);
			poly* diff = new poly();
			finddiff(diff->gethead(), p1->gethead(), p2->gethead());
			outfile<< "the diff of p1 and p2 is:\n";
			print(diff->gethead(), outfile);
			poly* prod = new poly();
			findprod(prod->gethead(), p1->gethead(), p2->gethead());
			outfile<< "the product of p1 and p2 is:\n";
			print(prod->gethead(), outfile);
		}
	}
};
int main(int argc, char* argv[]) {
	ifstream inFile;
	ofstream outfile;
	inFile.open("input.txt");
	outfile.open("output.txt");
	poly* p = new poly();
	p->construct(inFile, outfile);
	inFile.close();
	outfile.close();
}
