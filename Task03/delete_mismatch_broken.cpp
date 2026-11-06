int main(){int* data=new int[10];delete data;} // Intentional mismatch; sanitizer demonstration only.
