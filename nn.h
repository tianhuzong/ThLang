class Node{
        public:
        Node();
    };
class Type{
    Type();
};
class Value {
public:
    Value() = default;
    Value(const char* a) : str_(a) {}
    static Value fromString(const char* a) { return Value(a); }
private:
    std::string str_;
};
