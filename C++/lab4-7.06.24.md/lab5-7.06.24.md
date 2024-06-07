/*
1 0 
1 1 
before add
1 0 1 
delete id=3, elements=3
delete id=1, elements=2
delete id=2, elements=2
result of add
5350-124
end
delete id=2, elements=2
free(): double free detected in tcache 2
*/

#include <iostream>
#include <iomanip>

template <typename Element>
class DynamicTable{
private:
	unsigned int size;
	unsigned int idx; 
	Element *elements;
public:
    static int counter;
	int id;
	DynamicTable(){
		size = 0;
		idx = 0;
		//https://stackoverflow.com/a/20509811
		elements = nullptr;
		id = counter;
		counter++;
	}
	
	void addElement(Element element){
		Element * newTable;
		if (size == 0) {
			//https://stackoverflow.com/a/6833214
			try {
				elements = new Element[1];
				size = 1;
				idx = 0;
				elements[idx] = element;
			}catch (std::bad_alloc&) {
				std::cout<<"ERROR"<<std::endl;
				return;
			}
		} else {
			if (idx< size-1) {
				idx += 1;
				elements[idx] = element;
			} else {
				try {
					newTable = new Element[size*2];
					for(int i = 0; i<size; i++) {
						newTable[i] = elements[i];
					}
					size *= 2;
					idx += 1;
					delete [] elements;
					elements = newTable;
					elements[idx] = element;
				} catch (std::bad_alloc&) {
					std::cout<<"ERROR"<<std::endl;
					return;
				}
			}
		}
	}
	
	~DynamicTable(){
	    std::cout<<"delete id="<<id<<", elements="<<(idx+1)<<std::endl;
		delete [] elements;
	}
	
	Element getElement(unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		
		return elements[idx];
		
	}
	
	void updateElement(Element element, unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		elements[idx]=element;
	}
	
	void print(){
		int i;
		std::cout<<"size: "<< size <<", last element index: "<< idx <<std::endl;
		for(i=0; i<=idx; i++) {
			std::cout<<"index: " << i << ", element: " << elements[i] << std::endl;
		}	
	}
	
	Element& operator[](unsigned int idx){
		return elements[idx];
	}
	
	unsigned int count(){
		return idx+1;
	}
	
	DynamicTable(const DynamicTable &t){
	    std::cout<<"Copy constructor "<<t.id<<std::endl;
	    
	    size=t.size;
	    idx=t.idx;
	   // elements=t.elements;//to robi domyślny konstruktor kopiujący
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	}
	
	DynamicTable & operator= (const DynamicTable& t){
	    std::cout<<"Copy assignment "<<t.id<<std::endl;
	    if(elements !=nullptr){
	        delete [] elements;
	    }
	    size=t.size;
	    idx=t.idx;
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	   return *this;
	}
};

template <typename Element>
int DynamicTable<Element>::counter = 0;
	
class Binary{
	private:
		DynamicTable<char> digits;
	public:
		Binary(){}
		Binary(unsigned int n){
			unsigned int r,c;
			while (n > 0){
				r = n % 2;
				c = n / 2;
				n = c;
				digits.addElement(r);
			}
		}
		
		void print()
		{	
			for (int i=digits.count()-1 ; i>=0 ; i--){
				std::cout<<std::left<<std::setw(2) << static_cast<int>(digits[i]);
				
			}
			std::cout<<std::endl;
		}
		
		unsigned int count(){
			return digits.count();
		}
		
		char getBit(unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		
		    return digits.getElement(idx);
	    }
	
	    void updateBit(char value, unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		    digits.updateElement(value, idx);
	    }
	    
	    void addNextBit(char value){
		    digits.addElement(value);
	    }
};

Binary add(Binary b1, Binary b2)
{
	Binary result;
	int i=0;
	char c_in=0,c_out=0,d=0,d1=0,d2=0;
	while (true){
		c_in=c_out;
		if(i<b1.count() && i<b2.count()){
			d1=b1.getBit(i);
			d2=b2.getBit(i);
			if(d1+d2+c_in==0){
				d=0;
				c_out=0;
			}else if(d1+d2+c_in==1){
				d=1;
				c_out=0;
			}else if(d1+d2+c_in==2){
				d=0;
				c_out=1;
			}else if(d1+d2+c_in==3){
				d=1;
				c_out=1;
			}
			result.addNextBit(d);
		}else if(i==b1.count() && i==b2.count() && c_out==1){
		    result.addNextBit(c_out);
			break;
		}
		i += 1;
	}
	result.print();
	return result;
}

int main(){
	Binary b;
	Binary b1(2);
	Binary b2(3);
	b1.print();
	b2.print();
	std::cout<<"before add"<<std::endl;
	b = add(b1,b2);
	std::cout<<"result of add"<<std::endl;
	b.print();
	std::cout<<"end"<<std::endl;
}
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
1 0 
1 1 
before add
1 0 1 
delete id=3, elements=3
delete id=1, elements=2
delete id=2, elements=2
result of add
5350-124
end
delete id=2, elements=2
free(): double free detected in tcache 2
*/

#include <iostream>
#include <iomanip>

template <typename Element>
class DynamicTable{
private:
	unsigned int size;
	unsigned int idx; 
	Element *elements;
public:
	DynamicTable(){
		size = 0;
		idx = 0;
		//https://stackoverflow.com/a/20509811
		elements = nullptr;
	}
	
	void addElement(Element element){
		Element * newTable;
		if (size == 0) {
			//https://stackoverflow.com/a/6833214
			try {
				elements = new Element[1];
				size = 1;
				idx = 0;
				elements[idx] = element;
			}catch (std::bad_alloc&) {
				std::cout<<"ERROR"<<std::endl;
				return;
			}
		} else {
			if (idx< size-1) {
				idx += 1;
				elements[idx] = element;
			} else {
				try {
					newTable = new Element[size*2];
					for(int i = 0; i<size; i++) {
						newTable[i] = elements[i];
					}
					size *= 2;
					idx += 1;
					delete [] elements;
					elements = newTable;
					elements[idx] = element;
				} catch (std::bad_alloc&) {
					std::cout<<"ERROR"<<std::endl;
					return;
				}
			}
		}
	}
	
	~DynamicTable(){
		delete [] elements;
	}
	
	Element getElement(unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		
		return elements[idx];
		
	}
	
	void updateElement(Element element, unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		elements[idx]=element;
	}
	
	void print(){
		int i;
		std::cout<<"size: "<< size <<", last element index: "<< idx <<std::endl;
		for(i=0; i<=idx; i++) {
			std::cout<<"index: " << i << ", element: " << elements[i] << std::endl;
		}	
	}
	
	Element& operator[](unsigned int idx){
		return elements[idx];
	}
	
	unsigned int count(){
		return idx+1;
	}
	
	DynamicTable(const DynamicTable &t){
	    //std::cout<<"Copy constructor "<<t.id<<std::endl;
	    
	    size=t.size;
	    idx=t.idx;
	   // elements=t.elements;//to robi domyślny konstruktor kopiujący
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	}
	
	DynamicTable & operator= (const DynamicTable& t){
	    //std::cout<<"Copy assignment "<<t.id<<std::endl;
	    if(elements !=nullptr){
	        delete [] elements;
	    }
	    size=t.size;
	    idx=t.idx;
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	   return *this;
	}
};

	
class Binary{
	private:
		DynamicTable<char> digits;
	public:
		Binary(){}
		Binary(unsigned int n){
			unsigned int r,c;
			while (n > 0){
				r = n % 2;
				c = n / 2;
				n = c;
				digits.addElement(r);
			}
		}
		
		void print()
		{	
			for (int i=digits.count()-1 ; i>=0 ; i--){
				std::cout<<std::left<<std::setw(2) << static_cast<int>(digits[i]);
				
			}
			std::cout<<std::endl;
		}
		
		unsigned int count(){
			return digits.count();
		}
		
		char getBit(unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		
		    return digits.getElement(idx);
	    }
	
	    void updateBit(char value, unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		    digits.updateElement(value, idx);
	    }
	    
	    void addNextBit(char value){
		    digits.addElement(value);
	    }
	    
};

Binary shift(Binary b, unsigned int by){
    Binary bShifted;
    for ( int i = 0; i < by; i++) {
        bShifted.addNextBit(0);
    }
    for(int i=0;i<b.count();i++)
    {
        bShifted.addNextBit(b.getBit(i));
    }
    return bShifted;
}

Binary add(Binary b1, Binary b2)
{
	Binary result;
	int i=0;
	char c_in=0,c_out=0,d=0,d1=0,d2=0;
	
	int c1=b1.count();
	int c2=b2.count();
	
	if(c1>c2){
	    for(int i=0;i<c1-c2;i++){
	        b2.addNextBit(0);
	    }
	}else if(c2>c1){
	    for(int i=0;i<c2-c1;i++){
	        b1.addNextBit(0);
	    }
	}
	i=0;
	while (true){
		c_in=c_out;
		if(i<b1.count() && i<b2.count()){
			d1=b1.getBit(i);
			d2=b2.getBit(i);
			if(d1+d2+c_in==0){
				d=0;
				c_out=0;
			}else if(d1+d2+c_in==1){
				d=1;
				c_out=0;
			}else if(d1+d2+c_in==2){
				d=0;
				c_out=1;
			}else if(d1+d2+c_in==3){
				d=1;
				c_out=1;
			}
			result.addNextBit(d);
		}else if(i==b1.count() && i==b2.count() && c_out==1 ){
		    result.addNextBit(c_out);
			break;
		}else if(i==b1.count() && i==b2.count() && c_out==0 ){
			break;}
		i += 1;
	}
	return result;
}



int main(){
	Binary b;
	Binary b1(2);
	Binary b2(13);
	b1.print();
	b2.print();
	b = add(b1,b2);
	b.print();
	
	Binary b3(11);
	b=shift(b3,3);
	b.print();
;
}
# ================================================================================================================================
/*
1 0 
1 1 
before add
1 0 1 
delete id=3, elements=3
delete id=1, elements=2
delete id=2, elements=2
result of add
5350-124
end
delete id=2, elements=2
free(): double free detected in tcache 2
*/

#include <iostream>
#include <iomanip>

template <typename Element>
class DynamicTable{
private:
	unsigned int size;
	unsigned int idx; 
	Element *elements;
public:
	DynamicTable(){
		size = 0;
		idx = 0;
		//https://stackoverflow.com/a/20509811
		elements = nullptr;
	}
	
	void addElement(Element element){
		Element * newTable;
		if (size == 0) {
			//https://stackoverflow.com/a/6833214
			try {
				elements = new Element[1];
				size = 1;
				idx = 0;
				elements[idx] = element;
			}catch (std::bad_alloc&) {
				std::cout<<"ERROR"<<std::endl;
				return;
			}
		} else {
			if (idx< size-1) {
				idx += 1;
				elements[idx] = element;
			} else {
				try {
					newTable = new Element[size*2];
					for(int i = 0; i<size; i++) {
						newTable[i] = elements[i];
					}
					size *= 2;
					idx += 1;
					delete [] elements;
					elements = newTable;
					elements[idx] = element;
				} catch (std::bad_alloc&) {
					std::cout<<"ERROR"<<std::endl;
					return;
				}
			}
		}
	}
	
	~DynamicTable(){
		delete [] elements;
	}
	
	Element getElement(unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		
		return elements[idx];
		
	}
	
	void updateElement(Element element, unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		elements[idx]=element;
	}
	
	void print(){
		int i;
		std::cout<<"size: "<< size <<", last element index: "<< idx <<std::endl;
		for(i=0; i<=idx; i++) {
			std::cout<<"index: " << i << ", element: " << elements[i] << std::endl;
		}	
	}
	
	Element& operator[](unsigned int idx){
		return elements[idx];
	}
	
	unsigned int count(){
		return idx+1;
	}
	
	DynamicTable(const DynamicTable &t){
	    //std::cout<<"Copy constructor "<<t.id<<std::endl;
	    
	    size=t.size;
	    idx=t.idx;
	   // elements=t.elements;//to robi domyślny konstruktor kopiujący
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	}
	
	DynamicTable & operator= (const DynamicTable& t){
	    //std::cout<<"Copy assignment "<<t.id<<std::endl;
	    if(elements !=nullptr){
	        delete [] elements;
	    }
	    size=t.size;
	    idx=t.idx;
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	   return *this;
	}
};

	
class Binary{
	private:
		DynamicTable<char> digits;
	public:
		Binary(){}
		Binary(unsigned int n){
			unsigned int r,c;
			if(n==0){
			    digits.addElement(0);
			}else{
			    while (n > 0){
				    r = n % 2;
				    c = n / 2;
				    n = c;
				    digits.addElement(r);
			    }
			}
		}
		
		void print()
		{	
			for (int i=digits.count()-1 ; i>=0 ; i--){
				std::cout<<std::left<<std::setw(2) << static_cast<int>(digits[i]);
				
			}
			std::cout<<std::endl;
		}
		
		unsigned int count(){
			return digits.count();
		}
		
		char getBit(unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		
		    return digits.getElement(idx);
	    }
	
	    void updateBit(char value, unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		    digits.updateElement(value, idx);
	    }
	    
	    void addNextBit(char value){
		    digits.addElement(value);
	    }
	    
};

Binary shift(Binary b, unsigned int by){
    Binary bShifted;
    for ( int i = 0; i < by; i++) {
        bShifted.addNextBit(0);
    }
    for(int i=0;i<b.count();i++)
    {
        bShifted.addNextBit(b.getBit(i));
    }
    return bShifted;
}

Binary add(Binary b1, Binary b2)
{
	Binary result;
	int i=0;
	char c_in=0,c_out=0,d=0,d1=0,d2=0;
	
	int c1=b1.count();
	int c2=b2.count();
	
	if(c1>c2){
	    for(int i=0;i<c1-c2;i++){
	        b2.addNextBit(0);
	    }
	}else if(c2>c1){
	    for(int i=0;i<c2-c1;i++){
	        b1.addNextBit(0);
	    }
	}
	i=0;
	while (true){
		c_in=c_out;
		if(i<b1.count() && i<b2.count()){
			d1=b1.getBit(i);
			d2=b2.getBit(i);
			if(d1+d2+c_in==0){
				d=0;
				c_out=0;
			}else if(d1+d2+c_in==1){
				d=1;
				c_out=0;
			}else if(d1+d2+c_in==2){
				d=0;
				c_out=1;
			}else if(d1+d2+c_in==3){
				d=1;
				c_out=1;
			}
			result.addNextBit(d);
		}else if(i==b1.count() && i==b2.count() && c_out==1 ){
		    result.addNextBit(c_out);
			break;
		}else if(i==b1.count() && i==b2.count() && c_out==0 ){
			break;}
		i += 1;
	}
	return result;
}

Binary mul(Binary b1, Binary b2){
    Binary result(0);
    Binary s;
    Binary b1Zero;
    char b;
    for(int i=0;i<b1.count();i++){
        b1Zero.addNextBit(0);
    }

    for(int i=0;i<b2.count();i++){
        b=b2.getBit(i);
        if(b==0){
            s=shift(b1Zero,i);
        }else{
            s=shift(b1,i);
        }
        //std::cout<<"i= "<<i<<std::endl;
        //result.print();
        //s.print();
        result=add(result,s);
        //result.print();
    }
    return result;
}

int main(){
	Binary b;
	
	std::cout<<"ADD"<<std::endl;
	Binary b1(2);
	Binary b2(13);
	b1.print();
	b2.print();
	b = add(b1,b2);
	b.print();
	
	std::cout<<"MULL"<<std::endl;
	Binary b4(3);
	Binary b5(5);
	b4.print();
	b5.print();
	b=mul(b4,b5);
	b.print();
	return 0;
}

# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
1 0 
1 1 
before add
1 0 1 
delete id=3, elements=3
delete id=1, elements=2
delete id=2, elements=2
result of add
5350-124
end
delete id=2, elements=2
free(): double free detected in tcache 2
*/

#include <iostream>
#include <iomanip>
#include <cmath>
template <typename Element>
class DynamicTable{
private:
	unsigned int size;
	unsigned int idx; 
	Element *elements;
public:
	DynamicTable(){
		size = 0;
		idx = 0;
		//https://stackoverflow.com/a/20509811
		elements = nullptr;
	}
	
	void addElement(Element element){
		Element * newTable;
		if (size == 0) {
			//https://stackoverflow.com/a/6833214
			try {
				elements = new Element[1];
				size = 1;
				idx = 0;
				elements[idx] = element;
			}catch (std::bad_alloc&) {
				std::cout<<"ERROR"<<std::endl;
				return;
			}
		} else {
			if (idx< size-1) {
				idx += 1;
				elements[idx] = element;
			} else {
				try {
					newTable = new Element[size*2];
					for(int i = 0; i<size; i++) {
						newTable[i] = elements[i];
					}
					size *= 2;
					idx += 1;
					delete [] elements;
					elements = newTable;
					elements[idx] = element;
				} catch (std::bad_alloc&) {
					std::cout<<"ERROR"<<std::endl;
					return;
				}
			}
		}
	}
	
	~DynamicTable(){
		delete [] elements;
	}
	
	Element getElement(unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		
		return elements[idx];
		
	}
	
	void updateElement(Element element, unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		elements[idx]=element;
	}
	
	void print(){
		int i;
		std::cout<<"size: "<< size <<", last element index: "<< idx <<std::endl;
		for(i=0; i<=idx; i++) {
			std::cout<<"index: " << i << ", element: " << elements[i] << std::endl;
		}	
	}
	
	Element& operator[](unsigned int idx){
		return elements[idx];
	}
	
	unsigned int count(){
		return idx+1;
	}
	
	DynamicTable(const DynamicTable &t){
	    //std::cout<<"Copy constructor "<<t.id<<std::endl;
	    
	    size=t.size;
	    idx=t.idx;
	   // elements=t.elements;//to robi domyślny konstruktor kopiujący
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	}
	
	DynamicTable & operator= (const DynamicTable& t){
	    //std::cout<<"Copy assignment "<<t.id<<std::endl;
	    if(elements !=nullptr){
	        delete [] elements;
	    }
	    size=t.size;
	    idx=t.idx;
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	   return *this;
	}
};

	
class Binary{
	private:
		DynamicTable<char> digits;
	public:
		Binary(){}
		Binary(unsigned int n){
			unsigned int r,c;
			if(n==0){
			    digits.addElement(0);
			}else{
			    while (n > 0){
				    r = n % 2;
				    c = n / 2;
				    n = c;
				    digits.addElement(r);
			    }
			}
		}
		
		void print()
		{	
			for (int i=digits.count()-1 ; i>=0 ; i--){
				std::cout<<std::left<<std::setw(2) << static_cast<int>(digits[i]);
				
			}
			std::cout<<std::endl;
		}
		
		unsigned int count(){
			return digits.count();
		}
		
		char getBit(unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		
		    return digits.getElement(idx);
	    }
	
	    void updateBit(char value, unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		    digits.updateElement(value, idx);
	    }
	    
	    void addNextBit(char value){
		    digits.addElement(value);
	    }
	    unsigned long int toDecimal(){
	        int decimal = 0;
            int power = 0;
    
            for(int i =0; i<digits.count(); i++){
                decimal += digits[i] * pow(2, power);
                power++;
            }
        return decimal;
	    }
	    
};

class Decimal{
    private:
        Binary b;
    public:
        Decimal(){}
        Decimal(unsigned long int n){
            b=Binary(n);
        }
        
        unsigned long int toDecimal(){
            return b.toDecimal();
        }
        friend Decimal add(Decimal d1, Decimal d2);
        
        void print(){
            std::cout<<b.toDecimal()<<std::endl;
        }
};


Binary shift(Binary b, unsigned int by){
    Binary bShifted;
    for ( int i = 0; i < by; i++) {
        bShifted.addNextBit(0);
    }
    for(int i=0;i<b.count();i++)
    {
        bShifted.addNextBit(b.getBit(i));
    }
    return bShifted;
}

Binary add(Binary b1, Binary b2)
{
	Binary result;
	int i=0;
	char c_in=0,c_out=0,d=0,d1=0,d2=0;
	
	int c1=b1.count();
	int c2=b2.count();
	
	if(c1>c2){
	    for(int i=0;i<c1-c2;i++){
	        b2.addNextBit(0);
	    }
	}else if(c2>c1){
	    for(int i=0;i<c2-c1;i++){
	        b1.addNextBit(0);
	    }
	}
	i=0;
	while (true){
		c_in=c_out;
		if(i<b1.count() && i<b2.count()){
			d1=b1.getBit(i);
			d2=b2.getBit(i);
			if(d1+d2+c_in==0){
				d=0;
				c_out=0;
			}else if(d1+d2+c_in==1){
				d=1;
				c_out=0;
			}else if(d1+d2+c_in==2){
				d=0;
				c_out=1;
			}else if(d1+d2+c_in==3){
				d=1;
				c_out=1;
			}
			result.addNextBit(d);
		}else if(i==b1.count() && i==b2.count() && c_out==1 ){
		    result.addNextBit(c_out);
			break;
		}else if(i==b1.count() && i==b2.count() && c_out==0 ){
			break;}
		i += 1;
	}
	return result;
}
Decimal add(Decimal d1, Decimal d2){
    Decimal d;
    d1.b.print();
    d2.b.print();
    d.b= add(d1.b,d2.b);
    d.b.print();
    return d;
}
Binary mul(Binary b1, Binary b2){
    Binary result(0);
    Binary s;
    Binary b1Zero;
    char b;
    for(int i=0;i<b1.count();i++){
        b1Zero.addNextBit(0);
    }

    for(int i=0;i<b2.count();i++){
        b=b2.getBit(i);
        if(b==0){
            s=shift(b1Zero,i);
        }else{
            s=shift(b1,i);
        }
        //std::cout<<"i= "<<i<<std::endl;
        //result.print();
        //s.print();
        result=add(result,s);
        //result.print();
    }
    return result;
}

int main(){
	Binary b;
	
	std::cout<<"ADD"<<std::endl;
	Binary b1(2);
	Binary b2(13);
	b1.print();
	b2.print();
	b = add(b1,b2);
	b.print();
	
	std::cout<<"MULL"<<std::endl;
	Binary b4(3);
	Binary b5(5);
	b4.print();
	b5.print();
	b=mul(b4,b5);
	b.print();
	
	std::cout<<"DECIMAL"<<std::endl;
	Decimal d;
	Decimal d1(6);
	Decimal d2(7);
	d=add(d1,d2);
	d.print();
	return 0;
}
# ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
1 0 
1 1 
before add
1 0 1 
delete id=3, elements=3
delete id=1, elements=2
delete id=2, elements=2
result of add
5350-124
end
delete id=2, elements=2
free(): double free detected in tcache 2
*/

#include <iostream>
#include <iomanip>
#include <cmath>
template <typename Element>
class DynamicTable{
private:
	unsigned int size;
	unsigned int idx; 
	Element *elements;
public:
	DynamicTable(){
		size = 0;
		idx = 0;
		//https://stackoverflow.com/a/20509811
		elements = nullptr;
	}
	
	void addElement(Element element){
		Element * newTable;
		if (size == 0) {
			//https://stackoverflow.com/a/6833214
			try {
				elements = new Element[1];
				size = 1;
				idx = 0;
				elements[idx] = element;
			}catch (std::bad_alloc&) {
				std::cout<<"ERROR"<<std::endl;
				return;
			}
		} else {
			if (idx< size-1) {
				idx += 1;
				elements[idx] = element;
			} else {
				try {
					newTable = new Element[size*2];
					for(int i = 0; i<size; i++) {
						newTable[i] = elements[i];
					}
					size *= 2;
					idx += 1;
					delete [] elements;
					elements = newTable;
					elements[idx] = element;
				} catch (std::bad_alloc&) {
					std::cout<<"ERROR"<<std::endl;
					return;
				}
			}
		}
	}
	
	~DynamicTable(){
		delete [] elements;
	}
	
	Element getElement(unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		
		return elements[idx];
		
	}
	
	void updateElement(Element element, unsigned int idx){
		if(idx>this->idx){
			throw std::out_of_range("Index out of range");
		}
		elements[idx]=element;
	}
	
	void print(){
		int i;
		std::cout<<"size: "<< size <<", last element index: "<< idx <<std::endl;
		for(i=0; i<=idx; i++) {
			std::cout<<"index: " << i << ", element: " << elements[i] << std::endl;
		}	
	}
	
	Element& operator[](unsigned int idx){
		return elements[idx];
	}
	
	unsigned int count(){
		return idx+1;
	}
	
	DynamicTable(const DynamicTable &t){
	    //std::cout<<"Copy constructor "<<t.id<<std::endl;
	    
	    size=t.size;
	    idx=t.idx;
	   // elements=t.elements;//to robi domyślny konstruktor kopiujący
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	}
	
	DynamicTable & operator= (const DynamicTable& t){
	    //std::cout<<"Copy assignment "<<t.id<<std::endl;
	    if(elements !=nullptr){
	        delete [] elements;
	    }
	    size=t.size;
	    idx=t.idx;
	   elements=new Element[t.size];
	   for(int i=0;i<=t.idx;i++)
	   {
	       elements[i]=t.elements[i];
	   }
	   return *this;
	}
};
class Number{
    public:
        virtual void print()=0;
        virtual unsigned long int toDecimal()=0;
};
	
class Binary:public Number{
	private:
		DynamicTable<char> digits;
	public:
		Binary(){}
		Binary(unsigned int n){
			unsigned int r,c;
			if(n==0){
			    digits.addElement(0);
			}else{
			    while (n > 0){
				    r = n % 2;
				    c = n / 2;
				    n = c;
				    digits.addElement(r);
			    }
			}
		}
		
		void print()
		{	
			for (int i=digits.count()-1 ; i>=0 ; i--){
				std::cout<<std::left<<std::setw(2) << static_cast<int>(digits[i]);
				
			}
			std::cout<<std::endl;
		}
		
		unsigned int count(){
			return digits.count();
		}
		
		char getBit(unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		
		    return digits.getElement(idx);
	    }
	
	    void updateBit(char value, unsigned int idx){
		    if(idx >= digits.count()){
			    throw std::out_of_range("Index out of range");
		    }
		    digits.updateElement(value, idx);
	    }
	    
	    void addNextBit(char value){
		    digits.addElement(value);
	    }
	    unsigned long int toDecimal(){
	        int decimal = 0;
            int power = 0;
    
            for(int i =0; i<digits.count(); i++){
                decimal += digits[i] * pow(2, power);
                power++;
            }
        return decimal;
	    }
	    
};

class Decimal:public Number{
    private:
        Binary b;
    public:
        Decimal(){}
        Decimal(unsigned long int n){
            b=Binary(n);
        }
        
        unsigned long int toDecimal(){
            return b.toDecimal();
        }
        friend Decimal add(Decimal d1, Decimal d2);
        
        void print(){
            std::cout<<b.toDecimal()<<std::endl;
        }
};


Binary shift(Binary b, unsigned int by){
    Binary bShifted;
    for ( int i = 0; i < by; i++) {
        bShifted.addNextBit(0);
    }
    for(int i=0;i<b.count();i++)
    {
        bShifted.addNextBit(b.getBit(i));
    }
    return bShifted;
}

Binary add(Binary b1, Binary b2)
{
	Binary result;
	int i=0;
	char c_in=0,c_out=0,d=0,d1=0,d2=0;
	
	int c1=b1.count();
	int c2=b2.count();
	
	if(c1>c2){
	    for(int i=0;i<c1-c2;i++){
	        b2.addNextBit(0);
	    }
	}else if(c2>c1){
	    for(int i=0;i<c2-c1;i++){
	        b1.addNextBit(0);
	    }
	}
	i=0;
	while (true){
		c_in=c_out;
		if(i<b1.count() && i<b2.count()){
			d1=b1.getBit(i);
			d2=b2.getBit(i);
			if(d1+d2+c_in==0){
				d=0;
				c_out=0;
			}else if(d1+d2+c_in==1){
				d=1;
				c_out=0;
			}else if(d1+d2+c_in==2){
				d=0;
				c_out=1;
			}else if(d1+d2+c_in==3){
				d=1;
				c_out=1;
			}
			result.addNextBit(d);
		}else if(i==b1.count() && i==b2.count() && c_out==1 ){
		    result.addNextBit(c_out);
			break;
		}else if(i==b1.count() && i==b2.count() && c_out==0 ){
			break;}
		i += 1;
	}
	return result;
}
Decimal add(Decimal d1, Decimal d2){
    Decimal d;
    d1.b.print();
    d2.b.print();
    d.b= add(d1.b,d2.b);
    d.b.print();
    return d;
}
Binary mul(Binary b1, Binary b2){
    Binary result(0);
    Binary s;
    Binary b1Zero;
    char b;
    for(int i=0;i<b1.count();i++){
        b1Zero.addNextBit(0);
    }

    for(int i=0;i<b2.count();i++){
        b=b2.getBit(i);
        if(b==0){
            s=shift(b1Zero,i);
        }else{
            s=shift(b1,i);
        }
        //std::cout<<"i= "<<i<<std::endl;
        //result.print();
        //s.print();
        result=add(result,s);
        //result.print();
    }
    return result;
}

class Fractional: public Number{
    private:
        Decimal numerator;//licznik
        Decimal denominator;//mianownik
        
    public:
        Fractional(unsigned long int n, unsigned long int d){
            numerator=Decimal(n);
            denominator=Decimal(d);
        }
        void print(){
            numerator.print();
            std::cout<<"/"<<std::endl;
            denominator.print();
        }
        unsigned long int toDecimal(){
            double n=numerator.toDecimal();
            double d=denominator.toDecimal();
            
            return n/d;
        }
        double toDecimalReal(){
            double n=numerator.toDecimal();
            double d=denominator.toDecimal();
            
            return n/d;
        }
};

int main(){
    /*Number numbers[2];
	Binary b;
	
	Binary b1(19);
	
	Decimal d1(17);
	
	b1.print();
	std::cout<<b1.toDecimal()<<std::endl;
	d1.print();
	std::cout<<d1.toDecimal()<<std::endl;
    numbers[0]=b1;
    numbers[1]=d1;*/
    Number **numbers=new Number *[3];
    Binary *b1=new Binary(19);
    Decimal *d1=new Decimal(17);
    Fractional *f1=new Fractional(5,7);
    f1->print();
    //Number n;
    std::cout<<(f1->toDecimalReal())<<std::endl;
    numbers[0]=b1;
    numbers[1]=d1;
    numbers[2]=f1;
    for (int i=0;i<2;i++){
        numbers[i]->print();
        std::cout<<(numbers[i]->toDecimal())<<std::endl;
    }
	return 0;
}