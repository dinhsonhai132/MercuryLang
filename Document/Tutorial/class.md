# Classes in MercuryLang

Classes allow you to **define custom objects** with their own **attributes (variables)** and **methods (functions)**. You can also create **inheritance** relationships between classes.

---

## 1. Defining a Class

Use the `class` keyword followed by the class name. Class attributes are declared with `let`, and methods are defined using `func ... do ... end`.

**Syntax:**

```mercurylang
class <ClassName> do
    let attribute1 = <value>
    let attribute2 = <value>

    func method_name(params) do
        <statements>
    end
end
```

**Example:**

```mercurylang
class Animal do
    let name = ""
    let age = 0
end
```

---

## 2. Creating an Instance

Use the class name as a constructor to create an object:

```mercurylang
let my_animal = Animal()
```

---

## 3. Accessing Attributes

Access attributes using the `.` (dot) operator:

```mercurylang
print(my_animal.name)  # ""
print(my_animal.age)   # 0
```

---

## 4. Adding Methods

Methods are functions **inside a class** that can operate on class attributes. Use `this` to refer to the current object:

```mercurylang
class Dog extends Animal do
    name = "Dog"

    func set_age(r_age) do
        this.age = r_age
    end

    func set_name(r_name) do
        this.name = r_name
    end

    func bark() do
        print("Woof!")
    end
end
```

---

## 5. Using Methods

```mercurylang
let pup = Dog()
pup.set_name("Pup")
pup.set_age(12)

print(pup.name)  # Pup
print(pup.age)   # 12
pup.bark()       # Woof!
```

* `this` refers to the **current object instance**.
* You can **change attributes** of the object using methods.
* Inheritance allows `Dog` to use attributes and methods from `Animal`.

---

## 6. Inheritance

`extends` keyword allows a class to **inherit attributes and methods** from another class:

```mercurylang
class Dog extends Animal do
    # Dog inherits name and age from Animal
end
```

* `Dog` now has `name` and `age` automatically.
* You can also **override** attributes or methods in the subclass.

---

### ✅ Summary

Classes in MercuryLang help you **create reusable and organized objects** with attributes and methods. Inheritance allows you to **extend functionality** and reuse code efficiently.
