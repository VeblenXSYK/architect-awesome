# 一、简介

​		设计模式最大的作用就是在**变化**和**稳定**中间寻找隔离点，然后分离它们，从而来管理变化。如果软件全部变化或者全部稳定，设计模式都不合适。在采用设计模式之前，一定要**分辨出软件的稳定点与变化点**。

# 二、七大原则

## 1、开闭原则

- 对扩展开放，对更改封闭
- 类模块应该是可扩展的，但是不可修改

## 2、里氏代换原则

- 子类必须能够替换它们的基类（IS-A）
- 继承表达类型抽象

## 3、依赖倒置原则

![dip](img\design_pattern\dip.png)

- 高层模块（**稳定**）不应该依赖低层模块（**变化**），二者都应该依赖于抽象（**稳定**）。
- 抽象（**稳定**）不应该依赖于实现细节（**变化**），实现细节应该依赖于抽象（**稳定**）。

## 4、接口隔离原则

- 不应该强迫客户程序依赖它们不同的方法（**不必要的方法不要public出去**）
- 接口应该小而完备

## 5、迪米特法则

- 也就最少知道原则，一个对象尽量让其它对象保持最少的了解

## 6、合成复用原则

​		优化使用对象组合，而不是类继承：

- 类继承通常为“白箱复用”，对象组合通常为“黑箱复用”
- 继承在某种程序上破坏了封装性，子类父类耦合度高
- 而对象组合则只要求被组合的对象具有良好定义的接口，耦合度低

## 7、单一职责原则

- 一个类应该仅有一个引起它变化的原因
- 变化的方向隐含着类的责任

# 三、重构关键技法

## 1、静态绑定（早绑定） —> 动态绑定（晚绑定）

​		静态绑定的是对象的静态类型，发生在**编译期**；动态绑定的是对象的动态类型，发生在**运行期**。**只有涉及虚函数的地方才存在动态绑定。**

## 2、继承 —> 组合

# 四、设计模式

## 0、分类

**组件协作：**

- 模板方法模式
- 策略模式
- 观察者模式

**单一职责：**

- 装饰模式
- 桥接模式

**对象创建：**

- 简单工厂模式
- 工厂方法模式
- 抽象工厂模式
- 原型模式
- 建造者模式

**对象性能：**

- 单例模式

**接口隔离模式：**

- 外观模式
- 代理模式
- 中介者模式
- 适配器模式

**状态变化：**

- 状态模式

**数据结构：**

- 组合模式

## 1、模板方法模式

​		通过把不变行为（**稳定**）搬移到超类，而将一些步骤延迟（**变化**）到子类中，去除子类中的重复代码（**复用**）来体现它的优势。

```c++
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

## 2、策略模式

​		定义一系列算法，把它们一个个封装起来，并且使它们可互相替换（**变化**）。该模式使得算法可独立于使用它的客户程序（**稳定**）而变化（**扩展，子类化**）。

```c++
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

class ReplaceAlgorithmFactory
{
public:
	static ReplaceAlgorithm *Create(enum RA ra)
	{
		if(ra == LRU)
			return new LRU_ReplaceAlgorithm();	
		else if(ra == FIFO)
			return new FIFO_ReplaceAlgorithm();
		else if(ra == RANDOM)
			return new Random_ReplaceAlgorithm();
		else 
			return NULL;
	}
};

class Cache	//策略模式与简单工厂模式相结合，只暴露Cache类给客户端
{
private:
	ReplaceAlgorithm *m_ra;
public:
	Cache(enum RA ra) 
	{ 
		m_ra = ReplaceAlgorithmFactory::Create(ra);
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

![strategy](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/strategy.png)

## 3、观察者模式

​		定义对象间的一种一对多（**变化**）的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。

```c++
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
		cout << m_name << "------" << m_blog->GetStatus() << endl;
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
	Blog *blog = new BlogCSDN("Subject");
	Observer *observer = new ObserverBlog("Observer", blog);
	blog->Attach(observer);
	blog->SetStatus("发表观察者模式");
	blog->Notify();
	
	delete blog;
	delete observer;
	
	return 0;
}
```

UML图：

![observer](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/observer.png)

## 4、装饰模式

​		动态（**组合**）地给一个对象增加一些额外的职责。就增加功能而言，装饰模式比生成子类（**继承**）更为灵活 （**消除重复代码 &  减少子类个数**）

```c++
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
    Component *component;// 继承与组合字段的类型相同（这是装饰模式的特征）
public:
    void SetComponent(Component *c) {       // 设置Component
        component = c;
    }

    virtual void Operation() { // 重写Operation()，实际执行的是Component的Operation()
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
        cout << "ConcreteDecoratorA: addedState" << endl;
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
![observer](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/decorator.png)

## 5、桥接模式

​		将抽象部分与它的实现部分分离，使它们都可以独立地变化。桥接模式使用“**对象间的组合关系**”解耦抽象和实现之间固有的绑定关系，使得抽象和实现可以沿着各自的维度来变化。所谓抽象和实现沿着各自维度的变化，即“子类化”它们。

​		桥接模式有时候**类似于多继承方案**，但是多继承方案往往违背单一职责原则（即一个类只有一个变化的原因），复用性比较差，桥接模式是比多继承方案更好的解决方法。

```c++
#include <iostream>

using namespace std;

// 操作系统
class OS {
public:
	virtual void InstallOS_Imp() {}
};

class WindowOS: public OS {
public:
	void InstallOS_Imp() { cout << "安装Window操作系统" << endl; } 
};

class LinuxOS: public OS {
public:
	void InstallOS_Imp() { cout << "安装Linux操作系统" << endl; } 
};

// 计算机
class Computer {
public:
    virtual void InstallOS() {}
    void SetOS(OS *os) { this->os = os; }
protected:
    OS *os;
};

class DellComputer : public Computer {
public:
    void InstallOS() {
        os->InstallOS_Imp();
    }
};

class AppleComputer: public Computer
{
public:
	void InstallOS() { 
        os->InstallOS_Imp(); 
    }
};

int main() {

	Computer *computer1 = new AppleComputer();

    computer1->SetOS(new WindowOS());
	computer1->InstallOS();

    computer1->SetOS(new LinuxOS());
	computer1->InstallOS();

    return 0;
}
```

UML图：

![observer](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/bridge.png)

## 6、简单工厂模式

​		通过“对象创建”模式**绕开new**，来避免对象创建（new）过程中所导致的紧耦合（**依赖具体类**），从而支持**对象创建的稳定**。

​		主要特点是需要在工厂类中做判断，从而创造相应的产品。当增加新的产品时，就需要修改工厂类（**违反了开放封闭原则**）。

```c++
#include <iostream>

using namespace std;

enum CTYPE {COREA, COREB};
class SingleCore
{
public:
    virtual ~SingleCore(){}
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
	static SingleCore *CreateSingleCore(enum CTYPE ctype)
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
	SingleCore *sc = Factory::CreateSingleCore(COREA);
	sc->Show();
    delete sc;
	
	return 0;
}
```

UML图：

![factory1](img\design_pattern\factory1.png)

## 7、工厂方法模式

​		定义一个用于创建对象的接口（**工厂基类**），让子类决定实例化哪一个类。使得一个类的实例化延迟（**目的：解耦，手段：虚函数**）到子类。

​		主要特点是一个工厂抽象接口和多个具体生成对象的工厂。这样当新增加一个功能时，不需要更改原有的工厂类，只需要增加此功能的具体类和相应的工厂类就可以了，完全符合开放-封闭原则的精神。

```c++
#include <iostream>

using namespace std;

class SingleCore
{
public:
    virtual ~SingleCore(){}
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
    virtual ~Factory(){}
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
    //这里还是会依赖FactoryA具体的类，这是不可避免的
	Factory *factory = new FactoryA();
    
	SingleCore *singlecore = factory->CreateSingleCore();
	singlecore->Show();
    delete singlecore;
    delete factory;
	
	factory = new FactoryB();
    
	singlecore = factory->CreateSingleCore();
	singlecore->Show();
	delete singlecore;
    delete factory;
    
	return 0;
}
```

UML图：

![factory2](img\design_pattern\factory2.png)

## 8、抽象工厂模式

​		主要特点是为**创建一组相关或相互依赖的对象(没有则使用简单工厂即可)**提供一个接口，而无需指定它们具体的类。它是工厂方法模式的升级版本，与工厂方法模式的区别在于：工厂方法模式针对的是一个产品；而抽象工厂模式则是针对多个相关产品。

```c++
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

## 9、原型模式

​		在面临**某些结构复杂的对象的创建工作**,原型模式不用重新初始化对象，而是动态获得对象运行时的状态。

```c++
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
    // 通过克隆自己来创建对象
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

![observer](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/clone.png)

## 10、建造者模式

​		将**一个复杂对象**的构建与它的表示分离，使得同样的构建过程（**稳定**）可以创建不同的表示。与模板方法模式类似，不过它主要解决的是对象的创建工作。

```c++
#include <iostream>

using namespace std;

class Builder {
public:
    virtual void BuildHead() = 0;
    virtual void BuildBody() = 0;
    virtual void BuildLeftArm() = 0;
    virtual void BuildRightArm() = 0;
    virtual void BuildLeftLeg() = 0;
    virtual void BuildRightLeg() = 0;
};

// 构造瘦人
class ThinBuilder : public Builder {
public:
    void BuildHead() { cout << "build thin body" << endl; }
	void BuildBody() { cout << "build thin head" << endl; }
	void BuildLeftArm() { cout << "build thin leftarm" << endl; }
	void BuildRightArm() { cout << "build thin rightarm" << endl; }
	void BuildLeftLeg() { cout << "build thin leftleg" << endl; }
	void BuildRightLeg() { cout << "build thin rightleg" << endl; }
};

// 构造胖人
class FatBuilder : public Builder {
public:
    void BuildHead() { cout << "build Fat body" << endl; }
	void BuildBody() { cout << "build Fat head" << endl; }
	void BuildLeftArm() { cout << "build Fat leftarm" << endl; }
	void BuildRightArm() { cout << "build Fat rightarm" << endl; }
	void BuildLeftLeg() { cout << "build Fat leftleg" << endl; }
	void BuildRightLeg() { cout << "build Fat rightleg" << endl; }
};

// 构造指挥者
class Director {
private:
    Builder *m_pBuilder;
public:
    Director(Builder *buidler) { m_pBuilder = buidler; }
    void Create() {
        m_pBuilder->BuildHead();
        m_pBuilder->BuildBody();
        m_pBuilder->BuildLeftArm();
        m_pBuilder->BuildRightArm();
        m_pBuilder->BuildLeftLeg();
        m_pBuilder->BuildRightLeg();
    }
};

int main() {

    ThinBuilder thin;
    Director director1(&thin);
    director1.Create();

    FatBuilder fat;
    Director director2(&fat);
    director2.Create();

    return 0;
}
```

UML图：

![observer](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/build.png)

## 11、单例模式

​		保证一个类只有一个实例，并提供一个访问它的全局访问点。首先，需要保证一个类只有一个实例；在类中，要构造一个实例，就必须调用类的构造函数，如此，为了防止在外部调用类的构造函数而构造实例，需要将构造函数的访问权限标记为protected或private；最后，需要提供要给全局访问点，就需要在类中定义一个static函数，返回在类内部唯一构造的实例。

```c++
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

![single](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/single.png)

缺点：没有考虑到多线程的问题，在多线程的情况下，就可能创建多个Singleton实例，以下版本是改善的版本

```
#include <iostream>
#include <mutex> 

using namespace std;

class Singleton
{
public:
	static Singleton *GetInstance()
	{
		if(m_Instance == NULL)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			// 此处进行了两次m_Instance == NULL的判断，使用的所谓的“双检锁”机制。因为进行一次加锁和解锁是需要付出对应的代价的，而进行两次判断，就可以避免多次加锁与解锁操作，同时也保证了线程安全。
			if (m_Instance == NULL )
			{
                /*
                    为了执行下面一条代码，机器需要做三样事：
                        1、singleton对象分配空间       operator new(sizeof(Singleton))
                        2、在分配的空间中构造对象       new (_instance) Singleton;  
                        3、使_instance指向分配的空间    _instance =
                    遗憾的是编译器并不是严格按照上面的顺序来执行的，可能交换2和3。这样可能出现m_Instance不为NULL，但是对象并没有构造完全的情况，就造成了“双检锁”机制失效的问题，
                    解决这个问题的方法可以参考《Linux多线程服务端编程：使用muduo C++网络库》中 2.5 线程安全的Singleton实现
                */
				m_Instance = new Singleton();
			}
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
    static std::mutex m_mutex;
	int m_Test;
};
Singleton *Singleton::m_Instance = NULL;
std::mutex Singleton::m_mutex;

int main(int argc , char *argv [])
{
	Singleton *singletonObj = Singleton::GetInstance();
	cout<< singletonObj->GetTest() << endl;
	Singleton::DestoryInstance();
	
	return 0;
}
```

## 12、外观模式

​		为子系统中的**一组接口**提供一个一致（**稳定**）的界面，外观模式定义了一个高层接口，这个接口使得这一子系统更加容易使用（**复用**）。更注重从**架构**的层次上看整个系统，而不是单个类的层次，很多时候更是一种**架构设计模式**。**解决的是系统间的耦合**。

​		外观模式应该是用的很多的一种模式，特别是当一个系统很复杂时，系统提供给客户的是一个简单的对外接口，而把里面复杂的结构（**相互耦合关系比较大的一系列组件**）都封装了起来。客户只需使用这些简单接口就能使用这个系统，而不需要关注内部复杂的结构。举个编译器的例子，假设编译一个程序需要经过四个步骤：词法分析、语法分析、中间代码生成、机器码生成。学过编译都知道，每一步都很复杂。对于编译器这个系统，就可以使用外观模式。可以定义一个高层接口，比如名为Compiler的类，里面有一个名为Run的函数。客户只需调用这个函数就可以编译程序，至于Run函数内部的具体操作，客户无需知道。

```c++
#include <iostream>

using namespace std;

class Scanner {
public:
    void Scan() {
        cout << "词法分析" << endl;
    }
};

class Parser {
public:
    void Parse() {
        cout << "语法分析" << endl;
    }
};

class GenMidCode {
public:
    void GenCode() {
        cout << "产生中间代码" << endl;
    }
};

class GenMachineCode {
public:
    void GenCode() {
        cout << "产生机器码" << endl;
    }
};

// 高层接口
class Compiler
{
public:
    void Run() {
        Scanner scanner;
		Parser parser;
		GenMidCode genMidCode;
		GenMachineCode genMacCode;
		scanner.Scan();
		parser.Parse();
		genMidCode.GenCode();
		genMacCode.GenCode();
    }
};

int main() {

    Compiler compiler;
    compiler.Run();

    return 0;
}
```

UML图：

![observer](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/facade.png)

## 13、代理模式

​		为其他对象提供一种代理以控制对这个对象的访问。比如对象创建的开销很大，需要一些性能优化操作；或者某些操作需要安全控制；或者需要进程外的访问。直接访问会给使用者、或者系统结构带来很多麻烦。

```c++
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

![observer](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/proxy.png)

## 14、中介者模式

​		用一个中介对象来封装**多个对象交互**的情况。中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。**解决的是系统内对象之间的耦合。**

**核心思想：**

![mediator_core](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/mediator_core.png)

```c++
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
		cout << "租房者收到信息:" << message;
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
		cout << "房东收到信息:" << message;
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

![mediator](C:/Users/veblen/Desktop/architect-awesome/C++%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/img/design_pattern/mediator.png)

## 15、适配器模式

​		适配器模式将一个类的接口（**可能存在多个**）转换成客户希望的另外一个接口，使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。举个例子，在STL中就用到了适配器模式。STL实现了一种数据结构，称为双端队列（deque），支持前后两端的插入与删除。STL实现栈和队列时，没有从头开始定义它们，而是直接使用双端队列实现的。假设栈和队列都是一种顺序容器，有两种操作：压入和弹出。这里顺序容器为Target(客户所期待的接口)，栈与队列为Adapter(适配器)，双端队列为Adaptee(需要适配的类)。

​		应用于“希望复用一些现存的类，但是接口又与复用环境要求不一致的情况”，在遗留代码复用、类库迁移等方面非常有用。

```c++
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

## 16、状态模式

​		状态模式允许一个对象在其内部状态改变时改变它的行为。

```c++
#include <iostream>

using namespace std;

class Work;
class State {
public:
    virtual void WriteProgram(Work *w) = 0;
};

class Work {
private:
    State *current;
    double hour;        // "钟点"属性，状态转换的依据
    bool finish;        // "任务完成"属性，是否能下班的依据

public:
    Work(State *s) {
        finish = false;
        current = s;
    }
    ~Work() { delete current; }

    double GetHour(void) { return hour; }
    void SetHour(double value) { hour = value; }

    bool GetTaskFinished(void) { return finish; }
    void SetTaskFinished(bool value) { finish = value; }

    void SetState(State *s) { 
        delete current; 
        current = s; 
    }

    void WriteProgram() {
        current->WriteProgram(this);
    }
};

// 下班休息状态
class RestState : public State {
public:
    void WriteProgram(Work *w) {
        cout << "当前时间：" << w->GetHour() << " 点 下班回家了\n";
    }
};

// 睡眠状态
class SleepingState : public State {
public:
    void WriteProgram(Work *w) {
        cout << "当前时间：" << w->GetHour() << " 点 不行了，睡着了\n";
    }
};

// 晚间工作状态
class EveningState : public State {
public:
    void WriteProgram(Work *w) {
        if (w->GetTaskFinished()) {
            w->SetState(new RestState());     // 如果完成任务，则转入下班状态
            w->WriteProgram();
        } else {
            if (w->GetHour() < 21) {
                cout << "当前时间：" << w->GetHour() << " 点 加班哦，疲累之极\n";
            } else {
                w->SetState(new SleepingState());   // 超过21点，则转入睡眠工作状态
                w->WriteProgram();
            }
        }
    }
};

// 下午工作状态
class AfternoonState : public State {
public:
    void WriteProgram(Work *w) {
        if (w->GetHour() < 17) {
            cout << "当前时间：" << w->GetHour() << " 点 下午状态还不错，继续努力\n";
        } else {
            w->SetState(new EveningState());  // 超过17点，则转入傍晚工作状态
            w->WriteProgram();
        }
    }
};

// 中午工作状态
class NoonState : public State {
public:
    void WriteProgram(Work *w) {
        if (w->GetHour() < 13) {
            cout << "当前时间：" << w->GetHour() << " 点 饿了，午饭；犯困，午休\n";
        } else {
            w->SetState(new AfternoonState());  // 超过13点，则转入下午工作状态
            w->WriteProgram();
        }
    }
};

// 上午工作状态
class ForenoonState : public State {
public:
    void WriteProgram(Work *w) {
        if (w->GetHour() < 12) {
            cout << "当前时间：" << w->GetHour() << " 点 上午工作，精神百倍\n";
        } else {
            w->SetState(new NoonState());      // 超过12点，则转入中午工作状态
            w->WriteProgram();
        }
    }
};

int main() {

    Work *emergencyproj = new Work(new ForenoonState());
    emergencyproj->SetHour(9);
    emergencyproj->WriteProgram();
    emergencyproj->SetHour(10);
    emergencyproj->WriteProgram();
    emergencyproj->SetHour(12);
    emergencyproj->WriteProgram();
    emergencyproj->SetHour(13);
    emergencyproj->WriteProgram();
    emergencyproj->SetHour(14);
    emergencyproj->WriteProgram();
    emergencyproj->SetHour(17);
    emergencyproj->WriteProgram();

    emergencyproj->SetTaskFinished(false);
    emergencyproj->WriteProgram();

    emergencyproj->SetHour(19);
    emergencyproj->WriteProgram();
    emergencyproj->SetHour(22);
    emergencyproj->WriteProgram();

    return 0;
}
```

UML图：

![observer](img\design_pattern\state.png)

## 17、组合模式

​		将对象组合成**树形结构**以表示“部分-整体”的层次结构（**为一种数据结构模式**）。使得用户对单个对象和组合对象的使用具有一致性（**稳定**）。注意两个字“树形”。这种树形结构在现实生活中随处可见，比如一个集团公司，它有一个母公司，下设很多家子公司。不管是母公司还是子公司，都有各自直属的财务部、人力资源部、销售部等。对于母公司来说，不论是子公司，还是直属的财务部、人力资源部，都是它的部门。整个公司的部门拓扑图就是一个树形结构。

```c++
#include <iostream>
#include <list>
#include <memory>

using namespace std;

// 公司接口（抽象组件角色：Component）
class Company {
public:
	Company(string name) { m_name = name; }
	virtual ~Company(){}
	virtual void Add(std::shared_ptr<Company> &pCom){}
	virtual void Show(int depth) {}
protected:
	string m_name;
};

// 具体公司（组合角色：Composite）
class ConcreteCompany : public Company {
public:
	ConcreteCompany(string name): Company(name) {}
	virtual ~ConcreteCompany() {}
	void Add(std::shared_ptr<Company> &pCom) {          // 位于树的中间，可以增加子树
        m_listCompany.push_back(pCom); 
    }
	void Show(int depth) {
		for(int i = 0; i < depth; i++)
			cout<<"-";
		cout << m_name << endl;
		list<std::shared_ptr<Company> >::iterator iter = m_listCompany.begin();
		for(; iter != m_listCompany.end(); iter++)      // 显示下层结点
			// 多态调用
			(*iter)->Show(depth + 2);
	}
private:
	list<std::shared_ptr<Company> > m_listCompany;
};

// 具体的部门，财务部（叶子角色：Leaf）
class FinanceDepartment : public Company {
public:
	FinanceDepartment(string name):Company(name){}
	virtual ~FinanceDepartment() {}
	virtual void Show(int depth) {      // 只需显示，无需添加函数，因为已是叶结点
		for(int i = 0; i < depth; i++)
			cout<<"-";
		cout << m_name << endl;
	}
};

// 具体的部门，人力资源部（叶子角色：Leaf）
class HRDepartment : public Company {
public:
	HRDepartment(string name):Company(name){}
	virtual ~HRDepartment() {}
	virtual void Show(int depth) {      // 只需显示，无需添加函数，因为已是叶结点
		for(int i = 0; i < depth; i++)
			cout<<"-";
		cout << m_name << endl;
	}
};

int main() {

    std::shared_ptr<Company> root(new ConcreteCompany("总公司"));
    std::shared_ptr<Company> leaf1(new FinanceDepartment("财务部"));
    std::shared_ptr<Company> leaf2(new HRDepartment("人力资源部"));
	root->Add(leaf1);
	root->Add(leaf2);
 
	// 分公司A
    std::shared_ptr<Company> mid1(new ConcreteCompany("分公司A"));
    std::shared_ptr<Company> leaf3(new FinanceDepartment("财务部"));
    std::shared_ptr<Company> leaf4(new HRDepartment("人力资源部"));
	mid1->Add(leaf3);
	mid1->Add(leaf4);
	root->Add(mid1);

	// 分公司B
    std::shared_ptr<Company> mid2(new ConcreteCompany("分公司B"));
    std::shared_ptr<Company> leaf5(new FinanceDepartment("财务部"));
    std::shared_ptr<Company> leaf6(new HRDepartment("人力资源部"));
	mid2->Add(leaf5);
	mid2->Add(leaf6);
	root->Add(mid2);

	root->Show(0);

	return 0;
}
```

UML图：

![observer](img\design_pattern\component.png)
