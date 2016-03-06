# BuilderBuilder
This is a basically working XxxxxBuilder builder for Swift.

A builder is a very useful programming tool to make it easier to build some objects programmatically or making testings to be setup easily.

For some code like this:

```
class MyObject {
    var objectA: Int
    var objectB: Int
    var objectC: String
    var objectD: MyType?
    
    init(objectA: Int, objectB: Int, objectC: String, objectD: MyType?) {
        // initialization
    }
    
    // Other code...
}
```

Basically instead of calling the very long init method, it would be convenient to have a builder to build it.

```
let something = MyObjectBuilder()
    .withObjectA(xx)
    .withObjectC(yy)
    .build()
```

I'm getting tired to write the very similar builders. So I created this tool. This tool will work to generate a Builder template for the class.

An example of generated code:

```
class MyObjectBuilder {
    var objectA: Int
    var objectB: Int
    var objectC: String
    var objectD: MyType?
    
    init() {
        // TODO: initialize default values here
    }
    
    func build() -> MyObject {
        return MyObject(
            objectA: objectA,
            objectB: objectB,
            objectC: objectC,
            objectD: objectD)
    }
    
    func withObjectA(objectA: Int) -> Self {
        self.objectA = objectA
        return self
    }
    
    func withObjectB(objectB: Int) -> Self {
        self.objectB = objectB
        return self
    }
    
    func withObjectC(objectC: String) -> Self {
        self.objectC = objectC
        return self
    }
    
    func withObjectD(objectD: MyType?) -> Self {
        self.objectD = objectD
        return self
    }
}
```

As you can see, it's already very ready to use!
