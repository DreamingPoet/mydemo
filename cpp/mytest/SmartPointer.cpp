// 共享指针 shared_ptr类

#include <iostream>
#include <vector>
#include <string>


using namespace std;

class MyObject
{
public:

	MyObject(int i):index(i)
	{
		cout << "MyObject() new!" << index << endl;
	}

	~MyObject()
	{
		cout << "~MyObject() deleted!" << index << endl;
	}

	int index = -1;

};


using namespace std;
int main()
{
	// shared_ptr
	// 除了可以通过new来构造，还可以通过传入shared_ptr, unique_ptr, weak_ptr来构造。
	// 当我们调用release()时，当前指针会释放资源所有权，计数减一。当计数等于0时，资源会被释放。
	// 成员函数：

	// use_count 返回引用计数的个数

	// unique 返回是否是独占所有权(use_count 为 1)

	// swap 交换两个 shared_ptr 对象(即交换所拥有的对象)

	// reset 放弃内部对象的所有权或拥有对象的变更, 会引起原有对象的引用计数的减少

	// get 返回内部对象(指针), 由于已经重载了()方法, 因此和直接使用对象是一样的.如 shared_ptr<int> sp(new int(1)); 
	// 
	// sp 与 sp.get()是等价的。

	string* s1 = new string("s1");

	shared_ptr<string> ps1(s1);
	shared_ptr<string> ps2;
	ps2 = ps1;

	cout << ps1.use_count() << endl;	//2
	cout << ps2.use_count() << endl;	//2
	cout << ps1.unique() << endl;	//0

	string* s3 = new string("s3");
	shared_ptr<string> ps3(s3);

	cout << (ps1.get()) << endl;	//033AEB48
	cout << ps3.get() << endl;	//033B2C50
	swap(ps1, ps3);	//交换所拥有的对象
	cout << (ps1.get()) << endl;	//033B2C50
	cout << ps3.get() << endl;	//033AEB48

	cout << ps1.use_count() << endl;	//1
	cout << ps2.use_count() << endl;	//2
	ps2 = ps1;
	cout << ps1.use_count() << endl;	//2
	cout << ps2.use_count() << endl;	//2
	ps1.reset();	//放弃ps1的拥有权，引用计数的减少
	cout << ps1.use_count() << endl;	//0
	cout << ps2.use_count() << endl;	//1


	// 空智能指针
	shared_ptr<MyObject> sp;
	// 在堆内存中分配一个对象并初始化它，返回指向此对象的shared_ptr
	sp = make_shared<MyObject>(0);

	cout << "sp count = " << sp.use_count() << endl;

	// shared_ptr的拷贝和赋值
	// 当进行拷贝和赋值时，每个shared_ptr都会记录有多少个其他shared_ptr指向相同的对象。
	shared_ptr<MyObject> sp1(sp);

	cout << "sp count = " << sp.use_count() << endl;

	// 给sp2 赋值，令它指向一个地址
	// sp 的引用计数 +1
	shared_ptr<MyObject> sp2;
	sp2 = sp;

	cout << "sp count = " << sp.use_count() << endl;

	// 给sp3 赋值，令它指向一个地址
	// sp 的引用计数 +1
	shared_ptr<MyObject> sp3;
	sp3 = sp2;

	cout << "sp count = " << sp.use_count() << endl;

	// 新建对象
	shared_ptr<MyObject> sp4 = make_shared<MyObject>(1);;
	// 给sp2 赋值，令它指向另一个地址
	// sp4 的引用计数 +1
	// sp2 原来指向的对象的引用计数 -1
	// 引用计数为 0 时，自动释放
	sp2 = sp4;


	cout << "sp count = " << sp.use_count() << endl;



	// 判断 sp.use_count() 是否为 1 
	sp.unique();

	// 返回与 sp 共享对象的智能指针的数量，可能很慢，主要用于调试
	sp.use_count();


	// 如果你将shared_ptr存放于一个容器中，而后不再需要全部元素，
	// 而只使用其中一部分，要记得用erase删除不再需要的那些元素。

	// 使用new动态分配和初始化对象
	// 在堆空间分配的内存是无名的，因此new无法为其分配的对象命名，而是返回一个指向该对象的指针。
	MyObject* mop = new MyObject(2);

	// 默认情况下，动态分配的对象是默认初始化的，
	// 这意味着内置类型或组合类型的对象的值将是未定义的，
	// 而类类型对象将用默认构造函数进行初始化。
	string *ps = new string; // 初始化为空string
	int* pi = new int; // pi 指向一个未初始化的int

	// 我们可以直接使用直接初始化方式来初始化一个动态分配一个动态分配的对象。
	// 我们可以使用传统的构造方式，
	// 在新标准下，也可以使用列表初始化
	int* pii = new int(123);
	string* pss = new string("my string");
	vector<int> *pv = new vector<int>{1,2,3,4};


	// 也可以对动态分配的对象进行初始化，只需在类型名之后跟一对空括号即可；
	// 动态分配的const对象
	const int* pci = new const int(1024);
	// 分配并默认初始化一个const的空string
	const string *pcs = new const string;

	// 类似其他任何const对象，一个动态分配的const对象必须进行初始化。
	// 对于一个定义了默认构造函数的类类型，其const动态对象可以隐式初始化，
	// 而其他类型的对象就必须显式初始化。由于分配的对象就必须显式初始化。
	// 由于分配的对象是const的，new返回的指针就是一个指向const的指针。


	// 内存耗尽的情况会导致 new 分配内存失败
	// 如果分配失败，new会抛出异常：std：bad_alloc
	// 阻止抛出异常，如果分配失败，new返回一个空指针 nullptr
	// new (nothrow)int
	// 这种new 称为定位 new ，定位new表达式允许我们向new传递额外的参数
	// 在例子中我们传给它一个由标准库定义的nothrow的对象，如果将nothrow传递给new，我们的意图是告诉它不要抛出异常。
	// 如果这种形式的new不能分配所需内存，它会返回一个空指针。bad_alloc和nothrow都在头文件new中。


	// 为了防止内存耗尽，在堆内存使用完之后，必须将其归还给系统，使用delete归还。
	// 指针值和delete
	// 我们传递给delete的指针必须指向动态内存，或者是一个空指针。
	// 释放一块并非new分配的内存或者将相同的指针释放多次，其行为是未定义的。
	// 即使delete后面跟的是指向静态分配的对象或者已经释放的空间，编译还是能够通过，实际上是错误的。

	// 使用new和delete管理动态内存常出现的问题：
	//	（1）忘记delete内存
	//	（2）使用已经释放的对象
	// 	（3）同一块内存释放两次
	// delete 之后重置指针值 ptr = nullptr
	// 在delete之后，指针就变成了空悬指针，即指向一块曾经保存数据对象但现在已经无效的内存的地址
	// 有一种方法可以避免悬空指针的问题：在指针即将要离开其作用于之前释放掉它所关联的内存
	// 如果我们需要保留指针可以在delete之后将nullptr赋予指针，这样就清楚的指出指针不指向任何对象。
	// 动态内存的一个基本问题是可能多个指针指向相同的内存

	// shared_ptr和new结合使用
	// 如果我们不初始化一个智能指针，它就会被初始化成一个空指针，
	// 接受指针参数的智能指针是explicit的，因此我们不能将一个内置指针隐式转换为一个智能指针，
	// 必须直接初始化形式来初始化一个智能指针
	// shared_ptr<int> p1 = new int(1024); // 错误
	shared_ptr<int> pppiii(new int(1024)); //正确

	unique_ptr<int> up(new int(1024));
	up.reset();

	// 可以自定义 delete 释放对象
	// shared_ptr<int> p(p2 , mydelete)
	
	// 若 p.unique() == 1 则释放指向的对象
	// p.reset()

	// 若 p.unique() == 1 则释放指向的对象，并令 p 指向 q，q为内置指针类型
	// p.reset(q)

	// 若 p.unique() == 1 则用 mydelete 释放指向的对象，并令 p 指向 q，q为普通指针类型
	// p.reset(q, mydelete)

	// 不要混合使用普通指针和智能指针
	// 如果混合使用的话，智能指针自动释放之后，普通指针有时就会变成悬空指针，
	// 当将一个shared_ptr绑定到一个普通指针时，我们就将内存的管理责任交给了这个shared_ptr。
	// 一旦这样做了，我们就不应该再使用普通指针来访问shared_ptr所指向的内存了。
	// 也不要使用 get 初始化另一个智能指针或为智能指针赋值

	// sptr.get()


/*
// 	shared_ptr<int> p(new int(42));//引用计数为1
// 	int* q = p.get();//正确：但使用q时要注意，不要让它管理的指针被释放
// 	{
// 		//新程序块
// 		//未定义：两个独立的share_ptr指向相同的内存
// 		shared_ptr(q);
// 
// 	}//程序块结束，q被销毁，它指向的内存被释放
// 	int foo = *p;//未定义，p指向的内存已经被释放了
*/


	// p和q指向相同的一块内部才能，由于是相互独立创建，因此各自的引用计数都是1，当q所在的程序块结束时，q被销毁，这会导致q指向的内存被释放，p这时候就变成一个空悬指针，再次使用时，将发生未定义的行为，当p被销毁时，这块空间会被二次delete

		//其他shared_ptr操作
		// 可以使用reset来将一个新的指针赋予一个shared_ptr :

// 	p = new int(1024);//错误：不能将一个指针赋予shared_ptr
// 	p.reset(new int(1024));//正确。p指向一个新对象

	// 与赋值类似，reset会更新引用计数，如果需要的话，会释放p的对象。reset成员经常和unique一起使用，来控制多个shared_ptr共享的对象。在改变底层对象之前，我们检查自己是否是当前对象仅有的用户。如果不是，在改变之前要制作一份新的拷贝：

// 
// 	if (!p.unique())
// 		p.reset(new string(*p));//我们不是唯一用户，分配新的拷贝
// 	*p += newVal;//现在我们知道自己是唯一的用户，可以改变对象的值













/*

智能指针和异常
如果使用智能指针，即使程序块过早结束，智能指针也能确保在内存不再需要时将其释放，sp是一个shared_ptr,因此sp销毁时会检测引用计数，当发生异常时，我们直接管理的内存是不会自动释放的。如果使用内置指针管理内存，且在new之后在对应的delete之前发生了异常，则内存不会被释放。

使用我们自己的释放操作
默认情况下，shared_ptr假定他们指向的是动态内存，因此当一个shared_ptr被销毁时，会自动执行delete操作，为了用shared_ptr来管理一个connection，我们必须首先必须定义一个函数来代替delete。这个删除器函数必须能够完成对shared_ptr中保存的指针进行释放的操作。

智能指针陷阱：
（1）不使用相同的内置指针值初始化（或reset）多个智能指针。
（2）不delete get()返回的指针
（3）不使用get()初始化或reset另一个智能指针
（4）如果你使用get()返回的指针，记住当最后一个对应的智能指针销毁后，你的指针就变为无效了
（5）如果你使用智能指针管理的资源不是new分配的内存，记住传递给它一个删除器
#unique_ptr
某个时刻只能有一个unique_ptr指向一个给定对象，由于一个unique_ptr拥有它指向的对象，因此unique_ptr不支持普通的拷贝或赋值操作。
下表是unique的操作：




*/

// 
// unique_ptr<T> u1; 
// unique_ptr<T,D> u2; U2 使用一个可调用对象D 来释放指针
// unique_ptr<T, D> u(d); 用类型为D的对象d 代替delete
// 
// u = nullptr; 释放u指向的对象，并将 u 置为空
// u.release(); u放弃对指针的控制权，返回指针，将u置为空
// u.reset(); 释放u指向的对象
// u.reset(q); 释放指向的对象，令u指向q，q为普通指针
// u.reset(nullptr);


	// 虽然我们不能拷贝或者赋值unique_ptr，但是可以通过调用release或reset将指针所有权从一个（非const）unique_ptr转移给另一个unique







	/*
	//将所有权从p1（指向string Stegosaurus）转移给p2
unique_ptr<string> p2(p1.release());//release将p1置为空
unique_ptr<string>p3(new string("Trex"));
//将所有权从p3转移到p2
p2.reset(p3.release());//reset释放了p2原来指向的内存
	
	
	*/



// release成员返回unique_ptr当前保存的指针并将其置为空。因此，p2被初始化为p1原来保存的指针，而p1被置为空。
// reset成员接受一个可选的指针参数，令unique_ptr重新指向给定的指针。
// 调用release会切断unique_ptr和它原来管理的的对象间的联系。release返回的指针通常被用来初始化另一个智能指针或给另一个智能指针赋值。
// 不能拷贝unique_ptr有一个例外：我们可以拷贝或赋值一个将要被销毁的unique_ptr.最常见的例子是从函数返回一个unique_ptr.
// unique_ptr<int> clone(int p)
// {
// 	//正确：从int*创建一个unique_ptr<int>
// 	return unique_ptr<int>(new int(p));
// }

// 还可以返回一个局部对象的拷贝：


/*
unique_ptr<int> clone(int p)
{
	unique_ptr<int> ret(new int(p));
	return ret;
}

*/

// 向后兼容：auto_ptr
// 标准库的较早版本包含了一个名为auto_ptr的类，它具有uniqued_ptr的部分特性，但不是全部。
// 用unique_ptr传递删除器
// unique_ptr默认使用delete释放它指向的对象，我们可以重载一个unique_ptr中默认的删除器
// 我们必须在尖括号中unique_ptr指向类型之后提供删除器类型。在创建或reset一个这种unique_ptr类型的对象时，必须提供一个指定类型的可调用对象删除器。
// 
// #weak_ptr
// weak_ptr是一种不控制所指向对象生存期的智能指针，它指向一个由shared_ptr管理的对象，将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放，即使有weak_ptr指向对象，对象还是会被释放。
// weak_ptr的操作

// 
// weak_ptr<T> W;
// weak_ptr<T> W(sp);
// 
// w = p; p 可以是shared_ptr 或 weak_ptr
// W.reset();  置为空
// W.use_count(); 
// W.expired(); 是否过期 use_cout() 0 true, 1 false
// W.lock(); 如果过期，返回一个空shared_ptr, 否则返回一个指向w的对象的shared_ptr

 

// 
// 由于对象可能不存在，我们不能使用weak_ptr直接访问对象，而必须调用lock，此函数检查weak_ptr指向的对象是否存在。如果存在，lock返回一个指向共享对象的shared_ptr, 如果不存在，lock将返回一个空指针
// 
// #scoped_ptr
// scoped和weak_ptr的区别就是，给出了拷贝和赋值操作的声明并没有给出具体实现，并且将这两个操作定义成私有的，这样就保证scoped_ptr不能使用拷贝来构造新的对象也不能执行赋值操作，更加安全，但有了"++""–"以及“ * ”“->”这些操作，比weak_ptr能实现更多功能。
// 
// 







	// unique_ptr 
	// unique_ptr实现独占式拥有或严格拥有概念，保证同一时间内只有一个智能指针可以指向该对象
	// unique_ptr<string> p3(new string("auto"));   //#4
	// unique_ptr<string> p4；                       //#5
	// p4 = p3;//此时会报错！！



	//weak_ptr
	// share_ptr虽然已经很好用了，但是有一点share_ptr智能指针还是有内存泄露的情况，
	// 当两个对象相互使用一个shared_ptr成员变量指向对方，会造成循环引用，使引用计数失效，从而导致内存泄漏。
	// weak_ptr 是一种不控制对象生命周期的智能指针, 它指向一个 shared_ptr 管理的对象. 
	// 进行该对象的内存管理的是那个强引用的shared_ptr， weak_ptr只是提供了对管理对象的一个访问手段。
	// weak_ptr 设计的目的是为配合 shared_ptr 而引入的一种智能指针来协助 shared_ptr 工作, 
	// 它只可以从一个 shared_ptr 或另一个 weak_ptr 对象构造, 它的构造和析构不会引起引用记数的增加或减少。
	// weak_ptr是用来解决shared_ptr相互引用时的死锁问题,如果说两个shared_ptr相互引用,
	// 那么这两个指针的引用计数永远不可能下降为0,资源永远不会释放。
	// 它是对对象的一种弱引用，不会增加对象的引用计数，和shared_ptr之间可以相互转化，
	// shared_ptr可以直接赋值给它，它可以通过调用lock函数来获得shared_ptr。

	/*
	class B;	//声明
	class A
	{
	public:
		shared_ptr<B> pb_;
		~A()
		{
			cout << "A delete\n";
		}
	};

	class B
	{
	public:
		shared_ptr<A> pa_;
		~B()
		{
			cout << "B delete\n";
		}
	};

	void fun()
	{
		shared_ptr<B> pb(new B());
		shared_ptr<A> pa(new A());
		cout << pb.use_count() << endl;	//1
		cout << pa.use_count() << endl;	//1
		pb->pa_ = pa;
		pa->pb_ = pb;
		cout << pb.use_count() << endl;	//2
		cout << pa.use_count() << endl;	//2
	}

	int main()
	{
		fun();
		return 0;
	}
	*/

	// 可以看到fun函数中pa ，pb之间互相引用，两个资源的引用计数为2，当要跳出函数时，智能指针pa，pb析构时两个资源引用计数会减1，但是两者引用计数还是为1，导致跳出函数时资源没有被释放（A、B的析构函数没有被调用）运行结果没有输出析构函数的内容，造成内存泄露。如果把其中一个改为weak_ptr就可以了，我们把类A里面的shared_ptr pb_，改为weak_ptr pb_ ，运行结果如下：
/*
// 	1
// 		1
// 		1
// 		2
// 		B delete
// 		A delete
*/
// 这样的话，资源B的引用开始就只有1，当pb析构时，B的计数变为0，B得到释放，B释放的同时也会使A的计数减1，同时pa析构时使A的计数减1，那么A的计数为0，A得到释放。

// 注意：我们不能通过weak_ptr直接访问对象的方法，比如B对象中有一个方法print()，我们不能这样访问，pa->pb_->print()，因为pb_是一个weak_ptr，应该先把它转化为shared_ptr，如：

	// shared_ptr<B> p = pa->pb_.lock();
	// p->print();

/*
// 	weak_ptr 没有重载* 和->但可以使用 lock 获得一个可用的 shared_ptr 对象.注意, weak_ptr 在使用前需要检查合法性.
// 
// 		expired 用于检测所管理的对象是否已经释放, 如果已经释放, 返回 true; 否则返回 false.
// 
// 		lock 用于获取所管理的对象的强引用(shared_ptr).如果 expired 为 true, 返回一个空的 shared_ptr; 否则返回一个 shared_ptr, 其内部对象指向与 weak_ptr 相同.
// 
// 		use_count 返回与 shared_ptr 共享的对象的引用计数.
// 
// 		reset 将 weak_ptr 置空.
// 
// 		weak_ptr 支持拷贝或赋值, 但不会影响对应的 shared_ptr 内部对象的计数.
*/

// scoped_ptr
// scoped和weak_ptr的区别就是，给出了拷贝和赋值操作的声明并没有给出具体实现，并且将这两个操作定义成私有的，
// 这样就保证scoped_ptr不能使用拷贝来构造新的对象也不能执行赋值操作，更加安全，但有了"++""–"以及“ * ”“->”这些操作，比weak_ptr能实现更多功能。




// 
// 何时使用智能指针，何时使用原始指针
// 智能指针：责对象生命周期的管理；所以生命期对象全都由unique_ptr和shared_ptr来管理。
// 
// 原始指针：不负责对象生命周期管理；所以涉及对象的使用而不涉及对象生命周期的管理时，均通过原始指针来使用。
// 
// 
// 智能指针和原始指针进行转换和传参时可能存在被意外释放的问题，使用时需要注意。比如，
// 
// 对智能指针A获取原始指针a，传入某函数，函数内重新用a包装出智能指针B，那么函数退出B被销毁时，a所指资源已被释放，原智能指针A无法正常使用。（如果资源在栈上将导致程序崩溃）
// 
// 原始指针a指向某资源，它被包装成智能指针A后传给某函数，函数结束时A被销毁，所指向的资源也被释放，此时a也无法再使用。
// 
// 
// 所以，
// 
// 对于一个接受原始指针的函数（或代码块），切记不可再将传入的原始指针包装为智能指针。
// 
// 对于一个接受智能指针的函数（或代码块），切记不要直接将原始指针就地包装传入，而应该一开始就使用智能指针而非原始指针管理对象。
// 
// 








	return 0;
}
