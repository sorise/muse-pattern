### Mixin 继承

Mixin(**M**ix in) 是一种将若干功能独立的类通过继承的方式实现模块复用的C++模板编程技巧。其基本做法是将模板参数作为派生类的基类:

```cpp
template<typename... Mixins>
class MixinClass : public Mixins... {
  public:
    MixinClass() :  Mixins...() {}
  // ...
};
```



一句话总计：模板参数作为父类！