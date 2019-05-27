# 一、工厂模式

## 1、简单工厂模式

	主要特点是需要在工厂类中做判断，从而创造相应的产品。当增加新的产品时，就需要修改工厂类。

```
#include <iostream>

using namespace std;

enum CTYPE {COREA, COREB};
class SingleCore
{
public:
	virtual void Show() = 0;
};

//单核A
class SingleCoreA : public SingleCore
{
public:
	void Show(){ cout << "SingleCore A" << endl; }
};

//单核B
class SingleCoreB : public SingleCore
{
public:
	void Show(){ cout << "SingleCore B" << endl; }
};

//唯一的工厂，可以生产两种型号的处理器核，在内部判断
class Factory
{
public:
	SingleCore *CreateSingleCore(enum CTYPE ctype)
	{
		//工厂内部判断
		if(ctype == COREA)
			return new SingleCoreA();   //生产核A
		else if(ctype == COREB)
			return new SingleCoreB();   //生产核B
		else
			return NULL;
	}
};

int main()
{
	Factory fa;
	//SingleCore *sc = fa.CreateSingleCore(COREB);
	SingleCore *sc = (&fa)->CreateSingleCore(COREA);
	sc->Show();
	
	return 0;
}
```

	缺点：增加新的核类型时，就需要修改工厂类。这就违反了开放封闭原则：软件实体（类、模块、函数）可以扩展，但是不可修改。

UML图：

![factory1](img\design_pattern\factory1.png)

## 2、工厂方法模式

	主要特点是一个工厂抽象接口和多个具体生成对象的工厂。这样当新增加一个功能时，不需要更改原有的工厂类，只需要增加此功能的具体类和相应的工厂类就可以了，完全符合开放-封闭原则的精神。

```
#include <iostream>

using namespace std;

class SingleCore
{
public:
	virtual void Show() = 0;
};

//单核A
class SingleCoreA : public SingleCore
{
public:
	void Show(){ cout << "SingleCore A" << endl; }
};

//单核B
class SingleCoreB : public SingleCore
{
public:
	void Show(){ cout << "SingleCore B" << endl; }
};

class Factory
{
public:
	virtual SingleCore *CreateSingleCore() = 0;
};

//生产A核的工厂
class FactoryA : public Factory
{
public:
	SingleCoreA *CreateSingleCore() 
	{ 
		return new SingleCoreA; 
	}
};

//生产B核的工厂
class FactoryB : public Factory
{
public:
	SingleCoreB *CreateSingleCore()
    { 
    	return new SingleCoreB; 
    }
};

int main()
{
	FactoryA fa;
	SingleCore *sa = fa.CreateSingleCore();
	sa->Show();
	
	FactoryB fb;
	SingleCore *sb = fb.CreateSingleCore();
	sb->Show();
	
	return 0;
}
```

	缺点：每增加一种产品，就需要增加一个对象的工厂。显示，相比简单工厂模式，工厂方法模式需要更多的类定义。

UML图：

![factory2](img\design_pattern\factory2.png)

## 3、抽象工厂模式

	主要特点是定义为提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。

```
#include <iostream>

using namespace std;

class SingleCore
{
public:
	virtual void Show() = 0;
};

//单核A
class SingleCoreA : public SingleCore
{
public:
	void Show(){ cout << "SingleCore A" << endl; }
};

//单核B
class SingleCoreB : public SingleCore
{
public:
	void Show(){ cout << "SingleCore B" << endl; }
};

//多核
class MultiCore
{
public:
	virtual void Show() = 0;
};

class MultiCoreA : public MultiCore
{
public:
	void Show() { cout << "Multi Core A" << endl; }
};

class MultiCoreB : public MultiCore
{
public:
	void Show() { cout << "Multi Core B" << endl; }
};

//工厂
class CoreFactory
{
public:
	virtual SingleCore *CreateSingleCore() = 0;
	virtual MultiCore *CreateMultiCore() = 0;
};

//工厂A，专门用来生产A型号的处理器
class FactoryA : public CoreFactory
{
public:
	SingleCore *CreateSingleCore()
	{ 
		return new SingleCoreA; 
	}
	
	MultiCore *CreateMultiCore()
	{
		return new MultiCoreA;
	}
};

//工厂B，专门用来生产B型号的处理器
class FactoryB : public CoreFactory
{
public:
	SingleCore *CreateSingleCore() 
	{ 
		return new SingleCoreB; 
	}
	
	MultiCore *CreateMultiCore()
	{
		return new MultiCoreB;
	}
};

int main()
{
	FactoryA fa;
	SingleCore *sa = fa.CreateSingleCore();
	MultiCore *ma = fa.CreateMultiCore();
	sa->Show();
	ma->Show();
	
	FactoryB fb;
	SingleCore *sb = fb.CreateSingleCore();
	MultiCore *mb = fb.CreateMultiCore();
	sb->Show();
	mb->Show();
	
	return 0;
}
```

UML图：

![factory3](img\design_pattern\factory3.png)

# 二、策略模式

	工厂模式是为了创建对象，而策略模式是为了对同一种方法有不同的实现，通俗的做法都是用多态实现。

```
#include <iostream>

using namespace std;

//抽象接口
class ReplaceAlgorithm
{
public:
	virtual void Replace() = 0;
};

//三种具体的替换算法
class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace()
	{
		cout << "LRU replace algorithm" << endl;
	}
};

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
	void Replace()
	{
		cout << "FIFO replace algorithm" << endl;
	}
};

class Random_ReplaceAlgorithm: public ReplaceAlgorithm  
{  
public:  
    void Replace() 
	{ 
		cout << "Random replace algorithm" << endl; 
	}  
};  

//Cache需要用到的替换算法标签
enum RA {LRU, FIFO, RANDOM};

class Cache	//策略模式与简单工厂模式相结合，只暴露Cache类给客户端
{
private:
	ReplaceAlgorithm *m_ra;
public:
	Cache(enum RA ra) 
	{ 
		if(ra == LRU)
			m_ra = new LRU_ReplaceAlgorithm();	
		else if(ra == FIFO)
			m_ra = new FIFO_ReplaceAlgorithm();
		else if(ra == RANDOM)
			m_ra = new Random_ReplaceAlgorithm();
		else 
			m_ra = NULL;
	}
	~Cache() { delete m_ra; }
	void Replace() { m_ra->Replace(); }
};

int main()
{
	Cache cache(LRU);   //指定标签即可
	cache.Replace();
	
	return 0;
}
```

UML图：

![strategy](img\design_pattern\strategy.png)

# 三、适配器模式

	适配器模式将一个类的接口转换成客户希望的另外一个接口，使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。举个例子，在STL中就用到了适配器模式。STL实现了一种数据结构，称为双端队列（deque），支持前后两端的插入与删除。STL实现栈和队列时，没有从头开始定义它们，而是直接使用双端队列实现的。这里双端队列就扮演了适配器的角色。队列用到了它的后端插入，前端删除。而栈用到了它的后端插入，后端删除。假设栈和队列都是一种顺序容器，有两种操作：压入和弹出。

```
#include <iostream>

using namespace std;

//双端队列
class Deque
{
public:
	void push_back(int x) 
	{ 
		cout << "Deque push_back" << endl; 
	}
	void push_front(int x)
	{
		cout << "Deque push_front" << endl;
	}
	void pop_back()
	{
		cout << "Deque pop_back" << endl;
	}
	void pop_front()
	{
		cout << "Deque pop_front" << endl;
	}
};

//顺序容器
class Sequence
{
public:
	virtual void push(int x) = 0;
	virtual void pop() = 0;
};

//栈
class Stack : public Sequence
{
public:
	void push(int x)
	{
		deque.push_back(x);
	}
	void pop()
	{
		deque.pop_back();
	}
private:
	Deque deque;  //双端队列
};

//队列
class Queue : public Sequence
{
	void push(int x)
	{
		deque.push_back(x);
	}
	void pop()
	{
		deque.pop_front();
	}
private:
	Deque deque;  //双端队列
};

int main()
{
	Sequence *s1 = new Stack();
	Sequence *s2 = new Queue();
	
	s1->push(1); s1->pop();
	s2->push(1); s2->pop();
	
	delete s1; delete s2;
	
	return 0;
}
```

UML图：

![adapter](img\design_pattern\adapter.png)

# 四、单例模式

	保证一个类只有一个实例，并提供一个访问它的全局访问点。首先，需要保证一个类只有一个实例；在类中，要构造一个实例，就必须调用类的构造函数，如此，为了防止在外部调用类的构造函数而构造实例，需要将构造函数的访问权限标记为protected或private；最后，需要提供要给全局访问点，就需要在类中定义一个static函数，返回在类内部唯一构造的实例。

```
#include <iostream>

using namespace std;

class Singleton
{
public:
	static Singleton *GetInstance()
	{
		if (m_Instance == NULL )
		{
			m_Instance = new Singleton();
		}
		return m_Instance;
	}

	static void DestoryInstance()
	{
		if (m_Instance != NULL )
		{
			delete m_Instance;
			m_Instance = NULL ;
		}
	}

	// This is just a operation example
	int GetTest()
	{
		return m_Test;
	}

private:
	Singleton(){ m_Test = 10; }
	static Singleton *m_Instance;
	int m_Test;
};
Singleton *Singleton ::m_Instance = NULL;

int main(int argc , char *argv [])
{
	Singleton *singletonObj = Singleton ::GetInstance();
	cout<< singletonObj->GetTest() << endl;
	Singleton ::DestoryInstance();
	
	return 0;
}
```

UML图：

![single](img\design_pattern\single.png)

缺点：没有考虑到多线程的问题，在多线程的情况下，就可能创建多个Singleton实例，以下版本是改善的版本

```
#include <iostream>

using namespace std;

class Singleton
{
public:
	static Singleton *GetInstance()
	{
		if(m_Instance == NULL)
		{
			Lock();		//C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
			if (m_Instance == NULL )
			{
				m_Instance = new Singleton();
			}
			UnLock();	//C++没有直接的Lock操作，请使用其它库的Lock，比如Boost，此处仅为了说明
		}
		
		return m_Instance;
	}

	static void DestoryInstance()
	{
		if (m_Instance != NULL )
		{
			delete m_Instance;
			m_Instance = NULL ;
		}
	}

	// This is just a operation example
	int GetTest()
	{
		return m_Test;
	}

private:
	Singleton(){ m_Test = 10; }
	static Singleton *m_Instance;
	int m_Test;
};
Singleton *Singleton ::m_Instance = NULL;

int main(int argc , char *argv [])
{
	Singleton *singletonObj = Singleton ::GetInstance();
	cout<< singletonObj->GetTest() << endl;
	Singleton ::DestoryInstance();
	
	return 0;
}
```

	此处进行了两次m_Instance == NULL的判断，是借鉴了Java的单例模式实现时，使用的所谓的“双检锁”机制。因为进行一次加锁和解锁是需要付出对应的代价的，而进行两次判断，就可以避免多次加锁与解锁操作，同时也保证了线程安全。

# 五、观察者模式

	定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。可以举个博客订阅的例子，当博主发表新文章的时候，即博主状态发生了改变，那些订阅的读者就会收到通知，然后进行相应的动作，比如去看文章，或者收藏起来。博主与读者之间存在种一对多的依赖关系。

```
#include <iostream>
#include <string>
#include <list>

using namespace std;

//观察者
class Observer
{
public:
	Observer(){}
	virtual ~Observer(){}
	virtual void Update(){}
};

//博客
class Blog
{
public:
	Blog(){}
	virtual ~Blog(){}
	void Attach(Observer *observer) //添加观察者
	{
		m_observers.push_back(observer);
	}
	void Remove(Observer *observer)	//移除观察者
	{
		m_observers.remove(observer);
	}
	void Notify()					//通知观察者
	{
		list<Observer *>::iterator iter = m_observers.begin();
		for(; iter != m_observers.end(); iter++)
			(*iter)->Update();
	}
	virtual void SetStatus(string s)//设置状态
	{
		m_status = s;
	}
	virtual string GetStatus()		//获得状态
	{
		return m_status;
	}
private:
	list<Observer *> m_observers;   //观察者链表
protected:
	string m_status;				//状态
};

//具体观察者
class ObserverBlog : public Observer
{
public:
	ObserverBlog(string name, Blog *blog) : m_name(name), m_blog(blog){}
	~ObserverBlog(){}
	void Update()			//获得更新状态
	{
		string status = m_blog->GetStatus();
		cout << m_name << "------" << status << endl;
	}
private:
	string m_name;			//观察者名称
	Blog *m_blog;			//观察的博客，当然以链表形式更好，可以观察多个博客
};

//具体博客类
class BlogCSDN : public Blog
{
public:
	BlogCSDN(string name) : m_name(name){}
	~BlogCSDN(){}
	void SetStatus(string s)//具体设置状态信息
	{
		m_status = "CSDN通知：" + m_name + s;
	}
	string GetStatus()
	{
		return m_status;
	}
private:
	string m_name;			//博客名称
};

int main()
{
	Blog *blog = new BlogCSDN("chenqi");
	Observer *observer = new ObserverBlog("veblen", blog);
	blog->Attach(observer);
	blog->SetStatus("发表观察者模式");
	blog->Notify();
	delete blog;delete observer;
	
	return 0;
}

```

UML图：

![observer](img\design_pattern\observer.png)

# 六、中介者模式

	用一个中介对象来封装一系列对象交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。

```
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Mediator;

//抽象人
class Person
{
protected:
	Mediator *m_mediator;		//中介
public:
	virtual void SetMediator(Mediator *mediator){}		//设置中介
	virtual void SendMessage(string message){}			//向中介发送信息
	virtual void GetMessage(string message){}			//从中介获取信息
};

//抽象中介机构
class Mediator
{
public:
	virtual void Send(string message, Person *person){}
	virtual void SetA(Person *A){}	//设置其中一方
	virtual void SetB(Person *B){}
};

//租房者
class Renter : public Person
{
public:
	void SetMediator(Mediator *mediator)
	{
		m_mediator = mediator;
	}
	void SendMessage(string message)
	{
		m_mediator->Send(message, this);
	}
	void GetMessage(string message)
	{
		cout << "租房者收到信息" << message;
	}
};

//房东
class Landlord : public Person
{
	void SetMediator(Mediator *mediator)
	{
		m_mediator = mediator;
	}
	void SendMessage(string message)
	{
		m_mediator->Send(message, this);
	}
	void GetMessage(string message)
	{
		cout << "房东收到信息" << message;
	}
};

//房屋中介
class HouseMediator : public Mediator
{
private:
	Person *m_A;	//租房者
	Person *m_B;	//房东
public:
	HouseMediator() : m_A(0), m_B(0){}
	void SetA(Person *A)
	{
		m_A = A;
	}
	void SetB(Person *B)
	{
		m_B = B;
	}
	void Send(string message, Person *person)
	{
		if(person == m_A)				//租房者给房东发信息
			m_B->GetMessage(message);	//房东收到信息
		else
			m_A->GetMessage(message);
	}
};

int main()
{
	Mediator *mediator = new HouseMediator();
	Person *person1 = new Renter();		//租房者
	Person *person2 = new Landlord();	//房东
	mediator->SetA(person1);
	mediator->SetB(person2);
	person1->SetMediator(mediator);
	person2->SetMediator(mediator);
	person1->SendMessage("我想在南京路附近租套房子，价格800元一个月\n");
	person2->SendMessage("出租房子：南京路100号，70平米，1000元一个月\n");
	delete person1;delete person2;delete mediator;
	
	return 0;
}
```

UML图：

![mediator](img\design_pattern\mediator.png)

# 七、装饰模式

	装饰模式是为了已有功能动态添加更多功能的一种方式，python中装饰器就是采用的装饰模式。
```
#include <iostream>
#include <string>

using namespace std;

class Component { // 接口
public:
    virtual void Operation() = 0;
};

class ConcreteComponent : public Component { // 具体实现对象，需要被装饰的类
public:
    void Operation() {
        cout << "ConcreteComponent" << endl;
    }
};

class Decorator : public Component {        // 装饰基类
private:
    Component *component;
public:
    void SetComponent(Component *c) {       // 设置Component
        component = c;
    }

    virtual void Operation() {              // 重写Operation()，实际执行的是Component的Operation()
        if (component) {
            component->Operation();
        }
    }
};

class ConcreteDecoratorA : public Decorator {
private:
    string addedState;  // 本类的独有变量，区别于ConcreteDecoratorB
public:
    void Operation() {
        // 首先运行原Component的Operation()，再执行本类的功能，如 addedState，相当于对原Component进行了装饰
        Decorator::Operation();
        addedState = "New State";
        cout << "ConcreteDecoratorA: AddedBehavior" << endl;
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    void Operation() {
        // 首先运行原Component的Operation()，再执行本类的功能，如 AddedBehavior，相当于对原Component进行了装饰
        Decorator::Operation();
        AddedBehavior();
        cout << "ConcreteDecoratorB: AddedBehavior" << endl;
    }
private:
    void AddedBehavior() {  // 本类独有的方法，以区别于ConcreteDecoratorA

    }
};

int main() {

    Component *c = new ConcreteComponent();

    Decorator *da = new ConcreteDecoratorA();
    da->SetComponent(c);
    da->Operation();

    Decorator *db = new ConcreteDecoratorB();
    db->SetComponent(c);
    db->Operation();

    delete db;
    delete da;
    delete c;

    return 0;
}

```
UML图：
![observer](img\design_pattern\decorator.png)

# 八、代理模式

	代理模式就是为其他对象提供一种代理以控制对这个对象的访问，有四种常用的情况：1、远程代理；2、虚代理；3、保护代理；4、智能引用。下面的例子就是虚代理的情况。

```
#include <iostream>

using namespace std;

class Image {
public:
    Image(string name) : m_imageName(name){}
    virtual ~Image(){}
    virtual void Show(){}
protected:
    string m_imageName;
};

class BigImage : public Image {
public:
    BigImage(string name) : Image(name){}
    ~BigImage() {}
    void Show() {
        cout << "Show big image: " << m_imageName << endl;
    }
};

class BigImageProxy : public Image {
private:
    BigImage *m_bigImage;
public:
    BigImageProxy(string name) : Image(name), m_bigImage(NULL){}
    ~BigImageProxy() { delete m_bigImage; }
    void Show() {
        if (m_bigImage == NULL) {
            m_bigImage = new BigImage(m_imageName);
        }

        m_bigImage->Show();
    }
};

int main() {

    Image *image = new BigImageProxy("xxx.jpg"); 
    image->Show();
    delete image;

    return 0;
}
```
UML图：

![observer](img\design_pattern\proxy.png)

# 九、原型模式

	原型模式不用重新初始化对象，而是动态获得对象运行时的状态。
```
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Resume {
protected:
    char *name;
public:
    Resume() {}
    virtual ~Resume() {}
    virtual Resume *Clone() { return NULL; }
    virtual void Set(const char *str) {}
    virtual void Show() {}
};

class ResumeA : public Resume {
public:
    ResumeA(const char *str) {
        if (str == NULL) {
            name = new char[1];
            name[0] = '\0';
        } else {
            name = new char[strlen(str) + 1];
            strcpy(name, str);
        }
    }
    ResumeA(const ResumeA &r) {
        cout << "ResumeA copy constructor" << endl;
        name = new char[strlen(r.name) + 1];
        strcpy(name, r.name);
    }
    ~ResumeA() {
        delete [] name;
    }
    ResumeA *Clone() {
        return new ResumeA(*this);
    }
    void Set(const char *str) {
        delete name;
        name = new char[strlen(str) + 1];
        strcpy(name, str);
    }
    void Show() {
        cout << "ResumeA name:" << name << endl;
    }             
};

int main() {

    Resume *r1 = new ResumeA("2");
    Resume *r2 = r1->Clone();
    r1->Set("1");

    r1->Show();
    r2->Show();

    return 0;
}
```

UML图：

![observer](img\design_pattern\clone.png)

# 九、模板方法模式

	模板方法模式是通过把不变行为搬移到超类，去除子类中的重复代码来体现它的优势

```
#include <iostream>
#include <string>

using namespace std;

class Resume {
protected:
    virtual void SetPersonalInfo(){}
    virtual void SetEducation(){}
    virtual void SetWorkExp(){}
public:
    void FillResume() {
        SetPersonalInfo();
        SetEducation();
        SetWorkExp();
    }
};

class ResumeA : public Resume {
protected:
    void SetPersonalInfo() {
        cout << "A's PersonalInfo" << endl;
    }
    void SetEducation() {
        cout << "A's Education" << endl;
    }
    void SetWorkExp() {
        cout << "A's Work Experience" << endl;
    }
};

class ResumeB : public Resume {
protected:
    void SetPersonalInfo() {
        cout << "B's PersonalInfo" << endl;
    }
    void SetEducation() {
        cout << "B's Education" << endl;
    }
    void SetWorkExp() {
        cout << "B's Work Experience" << endl;
    }
};

int main() {

    Resume *ra = new ResumeA();
    ra->FillResume();
    delete ra;

    Resume *rb = new ResumeB();
    rb->FillResume();
    delete rb;

    return 0;
}
```

UML图：

![observer](img\design_pattern\template.png)