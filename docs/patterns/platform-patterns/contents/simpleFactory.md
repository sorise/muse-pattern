### [简单工厂模式]()

根据参数决定生成对象。

缺点是一旦有新的子类，需要修改具体的工厂方法。
```cpp
class Tool{
protected:
    std::string name;
public:
    const std::string & getName(){
        return name;
    }
    virtual  ~Tool() = default;
};
```


```cpp
//锤子
class Hammer: public Tool{
public:
    explicit Hammer(std::string _name){
        this->name = std::move(_name);
    }
    ~Hammer() override = default;
};
//镊子
class Tweezers :public Tool{
public:
    explicit Tweezers(std::string _name){
        this->name = std::move(_name);
    }
    ~Tweezers() override = default;
};

class Saw: public Tool{
public:
    explicit Saw(std::string _name){
        this->name = std::move(_name);
    }
    ~Saw() override = default;
};


Tool* ToolFactory(const std::string& _name){
    if (_name == "hammer"){
        return new Hammer(_name);
    }else if(_name == "saw"){
        return new Saw(_name);
    }else
        return new Tweezers(_name);
};

int main() {
    Tool * tik = ToolFactory("saw");
    Saw *saw = dynamic_cast<Saw*>(tik);

    delete saw;
    return 0;
}
```
