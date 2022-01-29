#include <iostream>
#include <string>

class sedan {
public:
    virtual ~sedan()= default;;
    [[nodiscard]] virtual std::string drive() const = 0;
};

class toyotaSedan : public sedan {
public:
    [[nodiscard]] std::string drive() const override {
        return "Toyota Sedan is drive";
    }
};

class mercedesSedan : public sedan {
    [[nodiscard]] std::string drive() const override {
        return "Mercedes Sedan is drive";
    }
};

class SUV {
public:
    virtual ~SUV()= default;;
    [[nodiscard]] virtual std::string drive() const = 0;
    [[nodiscard]] virtual std::string pull(const sedan &collaborator) const = 0;
};

class toyotaSUV : public SUV {
public:
    [[nodiscard]] std::string drive() const override {
        return "Toyota SUV is drive";
    }
    [[nodiscard]] std::string pull(const sedan &collaborator) const override {
        const std::string result = collaborator.drive();
        return "Toyota SUV is drive with ( " + result + " )";
    }
};

class mercedesSUV : public SUV {
public:
    [[nodiscard]] std::string drive() const override {
        return "Mercedes SUV is drive";
    }
    [[nodiscard]] std::string pull(const sedan &collaborator) const override {
        const std::string result = collaborator.drive();
        return "Mercedes SUV is drive with ( " + result + " )";
    }
};

class AbstractFactory {
public:
    [[nodiscard]] virtual sedan *CreateProductA() const = 0;
    [[nodiscard]] virtual SUV *CreateProductB() const = 0;
};

class toyotaFactory : public AbstractFactory {
public:
    [[nodiscard]] sedan *CreateProductA() const override {
        return new toyotaSedan();
    }
    [[nodiscard]] SUV *CreateProductB() const override {
        return new toyotaSUV();
    }
};

class mercedesFactory : public AbstractFactory {
public:
    [[nodiscard]] sedan *CreateProductA() const override {
        return new mercedesSedan();
    }
    [[nodiscard]] SUV *CreateProductB() const override {
        return new mercedesSUV();
    }
};

void ClientCode(const AbstractFactory &factory) {
    const sedan *product_a = factory.CreateProductA();
    const SUV *product_b = factory.CreateProductB();
    std::cout << product_b->drive() << "\n";
    std::cout << product_b->pull(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    auto *f1 = new toyotaFactory();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;
    std::cout << "Client: Testing the same client code with the second factory type:\n";
    auto *f2 = new mercedesFactory();
    ClientCode(*f2);
    delete f2;
    return 0;
}
