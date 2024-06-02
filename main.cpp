#include <iostream>
#include <cstdint>
#include <memory>
#include "ponder/di/di.hpp"


class SendMessageService {
public:
    virtual ~SendMessageService() = default;
    virtual void sendMessage(const std::string& message, const std::string& recipient) = 0;
};

class EmailService : public SendMessageService {
public:
    void sendMessage(const std::string& message, const std::string& recipient) override {
        // 实现发送电子邮件的逻辑
        std::cout << "Sending email: " << message << " to " << recipient << std::endl;
    }
};
class SMSService : public SendMessageService {
public:
    void sendMessage(const std::string& message, const std::string& recipient) override {
        // 实现发送短信的逻辑
        std::cout << "Sending SMS: " << message << " to " << recipient << std::endl;
    }
};


class Notification {
public:
    explicit Notification(std::shared_ptr<SendMessageService> messageService) : messageService_(std::move(messageService)) {

    }

    void notify(const std::string& message, const std::string& recipient) {
        messageService_->sendMessage(message, recipient);
    }
private:
    std::shared_ptr<SendMessageService> messageService_;
};

int main() {
    print_type<SendMessageService>();

    std::cout << PONDER_DI_VERSION << std::endl;
    std::cout << PONDER_DI_VERSION_STRING << std::endl;
    return 0;
}
