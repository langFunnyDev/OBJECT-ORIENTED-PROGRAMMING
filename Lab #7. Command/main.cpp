#include <iostream>
#include <string>
#include <utility>

class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() const = 0;
};

class SimpleCommand : public Command {
private:
    std::string pay_load_;

public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(std::move(pay_load)) {
    }
    void Execute() const override {
        std::cout << "I am a strong and independent command, I can handle the assigned action myself (" << this->pay_load_ << ")\n";
    }
};

class Receiver {
public:
    static void DoSomething(const std::string &a) {
        std::cout << "Receiver: Working on (" << a << ".)\n";
    }
    static void DoSomethingElse(const std::string &b) {
        std::cout << "Receiver: Working on (" << b << ".)\n";
    }
};

class ComplexCommand : public Command {
private:
    Receiver *receiver_;
    std::string a_;
    std::string b_;
public:
    ComplexCommand(Receiver *receiver, std::string a, std::string b) : receiver_(receiver), a_(std::move(a)), b_(std::move(b)) {}
    void Execute() const override {
        std::cout << "I am a complex team and I pass on the task: \n";
        Receiver::DoSomething(this->a_);
        Receiver::DoSomethingElse(this->b_);
    }
};

class Invoker {

private:
    Command *on_start_;
    Command *on_finish_;
public:
    ~Invoker() {
        delete on_start_;
        delete on_finish_;
    }

    void setOnStart(Command *command) {
        this->on_start_ = command;
    }
    void setOnFinish(Command *command) {
        this->on_finish_ = command;
    }

    void doSomethingImportant() {
        std::cout << "I`m started.\n";
        if (this->on_start_) {
            this->on_start_->Execute();
        }
        if (this->on_finish_) {
            this->on_finish_->Execute();
        }
        std::cout << "I`m finished\n";
    }
};

int main() {
    auto *invoker = new Invoker;
    auto *receiver = new Receiver;

    invoker->setOnStart(new SimpleCommand("Hello world!"));
    invoker->setOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));

    invoker->doSomethingImportant();

    delete invoker;
    delete receiver;

    return 0;
}
