#include<iostream>
#include<cmath> 
#include<string>
#include<ctime>
#include<exception> 
using namespace std;
class polynomial;


class Term{
	friend polynomial;
	friend ostream& operator<<(ostream& os,const polynomial& poly);
private:
	float coef;  //�Y�� 
	int exp;	//���� 
};


class polynomial{
	friend ostream& operator<<(ostream& os,const polynomial& poly);
	friend istream& operator>>(istream& is ,polynomial& poly);
	
public:
	polynomial(); //�غc�h����p(x)0 
	
	polynomial Add(polynomial poly);//�ۥ[ 
	
	polynomial Mult(polynomial poly);//�ۭ� 
	
	float Eval(float f);//�a�JX���ƭ� 
	
	void newSize(const float newcoef,const int newexp);//�}�C�����j�ɨϥ� 
private:
	Term *termArray;// �}�C 
	int capacity;// termArray �j�p 
	int terms;// �D�s�Ʀr 

};


 
polynomial::polynomial():capacity(2),terms(0){
	
	termArray = new Term[capacity];//��l�Ʀh���� 
}


void polynomial::newSize(const float newcoef,const int newexp){
	if(this->terms==this->capacity){//�p�G��e���Ƶ���}�C�e�q�A�N��ݭn�X�R 
		this->capacity*=2;//�Ŷ�������*2�� 
		Term *temp= new Term[this->capacity];//�Ф@�ӷs��2���j�}�C 
		copy(this->termArray,this->termArray+terms,temp);//�N�ª��s��2���j���}�C 
		delete[] this->termArray;//�R�ª�  
		this->termArray=temp;//�N�s���}�C���VtermArray 
	}
	this->termArray[this->terms].coef=newcoef;//�]�w�Y�� 
	this->termArray[this->terms++].exp=newexp;//�]�w���� 
}
 

//�ۥ[ 
polynomial polynomial::Add(polynomial poly) {
	polynomial result; //�Ω�s�x�[�k���G
	int *loc; //�O������ 
	loc = new int[poly.terms+this->terms]; //��loc���t��Ӧh�������Ƭۥ[���`�M 
	float *data;//�����Y�� 
	data = new float[poly.terms+this->terms];
	int use_len=0;//�������Ī���
	 
	for(int i=0;i<this->terms;i++){//�]�ثe�C�@�� 
		int t=-1;//�P�_�ϧ_�ۦP���� 
		for(int j=0;j<use_len;j++){ 
			if(this->termArray[i].exp==loc[j]){//�p�G�w�s�bloc��m 
				t=j;//������m 
				continue;
			}
		}
		if(t==-1){//���bloc�̭� 
			loc[use_len]=this->termArray[i].exp;//�s�W���� 
			data[use_len++]=this->termArray[i].coef;//�s�W�t�� 
		}
		else 
			data[t]+=this->termArray[i].coef;//�w�s�b->�ۥ[ 
	}
	for(int i=0;i<poly.terms;i++){//�]�ǤJ�h�����C�@�� 
		int t=-1;
		for(int j=0;j<use_len;j++){
			if(poly.termArray[i].exp==loc[j]){
				t=j;
			continue;
			}	
		}
	
		if(t==-1){
			loc[use_len]= poly.termArray[i].exp;
			data[use_len++]=poly.termArray[i].coef;
		}
		else
			data[t]+=poly.termArray[i].coef;
	} 
	for(int i=0;i<use_len;i++){// �N loc �M data �����ȥ[�J���G�h����
		result.newSize(data[i],loc[i]);// �s�W���ب쵲�G�h����
	}
	return result; 
} 

//�ۭ� 
polynomial polynomial::Mult(polynomial poly){
	polynomial result;
	int *loc;
	loc=new int[poly.terms*this->terms];//���Ƭۭ��`�M 
	float *data;
	data = new float[poly.terms*this->terms];//�t�ƽc���`�M 
	int use_len=0;//���Ī��� 
	for(int i=0;i<this->terms;i++){//�]��e�h���O�C�@�� 
		for(int j=0;j<poly.terms;j++){//�]��J�h�����C�@�� 
			float t_coef = this->termArray[i].coef*poly.termArray[j].coef;//�p�ⶵ�Ƭۭ� 
			int t_exp = this->termArray[i].exp+poly.termArray[j].exp;//�p��Y�Ƭۥ[ 
			int t=-1;//��Ӽ� 
			for(int k=0;k<use_len;k++){//�]�ӼƦ�m 
				if(t_exp==loc[k]){ // �p�L�ӼƬۦP 
				t=k;//������e��m 
				continue;}
			}
		if(t==-1){//�N��Өt�Ƹ̭��S���� 
			loc[use_len]= t_exp;//�O���s���t��
			data[use_len++]= t_coef;
		} 
		else
			data[t]+=t_coef;//�p�G�w�s�b�A�ۥ[ 
		} 
	
	
	
	
	}
	for(int i=0;i<use_len;i++)
		result.newSize(data[i],loc[i]);
	return result;
}	
	
	
float polynomial::Eval(float x){//�a�Jx�D�� 
	float result = 0.0f;//��Ȭ�0 
	for(int i=0;i<this->terms;i++){ 
		float temp = this->termArray[i].coef;//��o��e�Y�� 
		for(int j=0;j<this->termArray[i].exp;j++){//��x���� 
			temp *=x ;//���H���� 
			
		}
		result+=temp;//�[�` 
	}
	return result;//�^�� 
}	

istream& operator>>(istream& is,polynomial& poly){
	float t_coef;
	int t_exp;
	char tmp;
	bool plus = true;
	while(1){
		is>>t_coef; //Ū�J�Y�� 
		if(!plus){
			t_coef*=-1;
			plus = true; 
		}
		is.get(tmp);//Ū�U�Ӧr���A�i��O'x'`'\0' 
		if(tmp=='\n'){//�p�G�O\0�A��ܱ`�� 
			poly.newSize(t_coef,0);//�s�W����0��Term 
			break;//�S�U�@�ӭ� 
		}
		is.ignore(1);//����'^' 
		is>>t_exp;//Ū���� 
		poly.newSize(t_coef,t_exp);//�s�W���� 
		is.get(tmp);//Ū�U�@�� 
		if(tmp== '\n') break;//�P�_�O���O���� 
		else if(tmp=='-')plus = false;//�p�G�O'-'�N��t�� 
	}
	return is;
}
ostream& operator<<(ostream& os,const polynomial& poly){
	for(int i=0;i<poly.terms;i++){
		if(poly.termArray[i].exp==0){//�p�G�O�`�ơA�u��X�Ʀr 
			os<<(poly.termArray[i].coef<0?"":"+")<<poly.termArray[i].coef;
			continue;
		}	
		if(i==0)//ax^n 
			os << poly.termArray[i].coef << "x^" << poly.termArray[i].exp;
		else//+ax^n
			os<<(poly.termArray[i].coef<0?"":"+")<<poly.termArray[i].coef<<"x^"<<poly.termArray[i].exp;
	}
	return os;
}



int main(){
	clock_t start,finish;
	cout<<"��J�榡 ax^n2+bx^n1+c (�`�Ƥ���^n0)"<<endl;
	polynomial p1,p2;
	cout<<"p1: ";
	cin>>p1;
	cout<<"p2: ";
	cin>>p2;
	cout<<endl;
	cout << "Polynomial��Eval()\n";
	float f = 0.0f;
	cout << "�п�Jf�ȡG";
	cin >> f;
	cout << "�h�����G" << p1 << endl;
	cout << "���G = " << p1.Eval(f) << endl;
	cout<<endl<<"polynomial��Add()\n";
	cout<<"p1= "<<p1<<endl;
	cout<<"p2= "<<p2<<endl;
	start=clock();
	cout<<"("<<p1<<")+("<<p2<<")="<<p1.Add(p2)<<endl;
	finish=clock();
	cout<<"Add()�ݮ�"<<(double)(finish-start)/CLOCKS_PER_SEC<<"s"<<endl<<endl;
	cout<<"polynomial��Mult()\n";
	cout<<"p1= "<<p1<<endl;
	cout<<"p2= "<<p2<<endl;
	start=clock();
	cout<<"("<<p1<<")*("<<p2<<")="<<p1.Mult(p2)<<endl;
	finish=clock();
	cout<<"Mult()�ݮ�: "<<(double)(finish-start)/CLOCKS_PER_SEC<<"s"<<endl;
	return 0;
} 
