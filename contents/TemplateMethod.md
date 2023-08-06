### [Template Method 模式](#)

**介绍**： 属于组件协作模式，通过晚期绑定，来实现框架与应用程序之间的松耦合。

-----

**动机**：在系统的设计开发过程中经常会遇到：对于某一个业务逻辑的算法实现对于不同的对象中有着不同的内部细节实现，但是整体的逻辑运行框架是相同的。Template 提供了这种情况的一个实现框架。Template 模式采用继承的方式实现，其将逻辑框架放在抽象基类中，并定义好具体接口，然后在子类中实现具体运算细节。

在软件构建过程中，对于某一项任务，它常常有稳定的整体操作结构，但各个子步骤却有很多改变的需求，或者由于固有的原因（比如框架与应用之间的关系）而无法和任务的整体结构同时实现。在确定稳定操作结构的前提下，来灵活应对各个子步骤的变化或者晚期实现需求



**Template 模式本质上还是利用多态的概念实现算法实现细节和高层接口的松耦合**。可以看到 Template 模式采取的是继承方式实现这一点的，当然，继承也会给这种设计模式带来一些不方便的地方



#### 模式定义

定义一个操作中的算法的稳定骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

除了可以灵活应对子步骤的变化外，“不要调用我，让我来调用你”的反向控制结构是Template Method的典型应用。

在具体实现方面，被Template Method 调用的虚方法可以具有实现，也可以没有任何实现（抽象方法、纯虚方法），但一般推荐将它们设置为protected方法。

#### 例子：

如下定义一个游戏类，其流程是稳定的，游戏的细节是变化的。

```cpp
class Game {
    virtual void initialize() = 0;
    virtual void startPlay() = 0;
    virtual void endPlay() = 0;
    //模板
public:
    void play(){
        //初始化游戏
        initialize();

        //开始游戏
        startPlay();

        //结束游戏
        endPlay();
    }
};

class Cricket: public Game {

    void endPlay() override{
        std::cout << "Cricket Game Finished!" << std::endl;
    }

    void initialize() override {
        std::cout << "Cricket Game Initialized! Start playing." << std::endl;
    }

    void startPlay() override {
        std::cout << "Cricket Game Started. Enjoy the game!"<< std::endl;
    }
};

```

获取库的调用步骤：

```cpp
class Library{
public:
    void Run(){

        Step1();

        if (Step2()) { //Step2 是变化的
            Step3();
        }

        for (int i = 0; i < 4; i++){
            Step4(); //Step4() 是变化的
        }

        Step5();

    }
    virtual ~Library(){ }

protected:
    void Step1() {
        //.....
    }
    void Step3() {
        //.....
    }
    void Step5() {
        //.....
    }

    virtual bool Step2() = 0;
    virtual void Step4() =0;
};
```

