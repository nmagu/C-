#include <iostream>
#include <vector>

using namespace std;

class VecInt
{
    private:
    int* a;
    int sz;
    int cp;
    
    void growIfFull();
    
    public:
    
    VecInt()
    : a(nullptr), sz(0), cp(0)
    {
    }
	
	VecInt(const VecInt& other);
    
    VecInt& operator=(const VecInt& other);
        
    void pushBack(int x);
    int* insert(int* pos, int x);
    int* erase(int* pos);
    
	int size() const
	{
		return sz;
	}
	
	const int& operator[](int index) const
	{
		return a[index];
	}
	
	int& operator[](int index) 
	{
		return a[index];
	}
	
    int* begin() const
    {
        return a;
    }
    
    int* end() const
    {
        return a + sz;
    }
    
    ~VecInt()
    {
        delete[] a;
    }
};

VecInt::VecInt(const VecInt& other)
: sz(other.sz), cp(other.sz)
{
    a = new int[sz];
    for (int i = 0; i < sz; ++i)
    {
        a[i] = other.a[i];
    }
}
    
VecInt& VecInt::operator=(const VecInt& other)
{
    if (this != &other)
    {
        sz = other.sz;
        cp = other.cp;
        int* p = new int[cp];
        
        for (int i = 0; i < other.sz; ++i)
        {
            p[i] = other.a[i];
        }
        
        delete[] a;
        a = p;
    }
    
    return *this;
}

void VecInt::growIfFull()
{
   if (sz == cp)
    {
        cp = cp == 0 ? 1: 2 * cp;
        int* p = new int[cp];
        
        for (int i = 0; i < sz; ++i)
        {
            p[i] = a[i];
        }
        
        delete[] a;
        a = p;
    } 
}
    
void VecInt::pushBack(int x)
{
    growIfFull();
    a[sz] = x;
    ++sz;
}

int* VecInt::insert(int* pos, int x)
{
    int indPos = pos - a; // you have to use this index to the insertion's position
                          // because growIfFill() can delete the old block of memory 
                          // and invalidate pointer pos
    growIfFull();
    
    int* newPos = a + indPos;
    for (int* q = a + sz; q != newPos; --q)
    {
        *q = *(q - 1);
    }
    
    *newPos = x;
    
    ++sz;
    
    return newPos;
}

int* VecInt::erase(int* pos)
{
    for (int* q = pos + 1; q != a + sz; ++q)
    {
        *(q - 1) = *q;
    }
    
    --sz;
    
    return pos;
}

bool operator==(const VecInt& a, const VecInt& b)
{
	if (a.size() != b.size())
	{
		return false;
	}
	
	for (int i = 0; i < a.size(); ++i)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	
	return true;
}

bool operator!=(const VecInt& a, const VecInt& b)
{
	return !(a == b);
}

int main()
{
    VecInt v;
    int x;
    while (cin >> x)
    {
        v.pushBack(x);
    }
    
    auto it = v.begin();
    while (it != v.end())
    {
        if (*it % 2 == 0)
        {
            it = v.insert(it, 0); // result of v.insert(it, 0) must be assigned to it
                                  // because the old value of pointer it might be incorrect (Why?)
            ++it;
        }
        ++it;
    }
    
    for (int e: v)
    {
        cout << e << " ";
    }
    cout << endl;
    
    it = v.begin();
    while (it != v.end())
    {
        if (*it % 2 == 0)
        {
            it = v.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    for (int e: v)
    {
        cout << e << " ";
    }
    cout << endl;
    
    return 0;
}