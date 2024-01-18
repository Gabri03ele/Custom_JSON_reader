int main() {
    json a;
     
    try {
        std::cin>> a;
        std::cout<< a;
    } catch (json_exception error) {
        std::cout<< error.msg;
    }
    std::cout<<std::endl;

    return 0;
}
