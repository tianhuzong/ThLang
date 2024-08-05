static llvm::LLVMContext MyContext;

class CodeGenContext {
    
    public :
        Module *module;
        
        CodeGenContext(std::string module_name) {module = new Module(module_name,MyContext);}
        void codeGen(std::vector<Node*> nodes);

};
