#include <iostream>
#include <Windows.h>
#include <processthreadsapi.h>

using namespace std;

HMODULE dllHandle;


//you might need to define more parameters and functionpointers to pass to your exported functions. I'm assuming void function in this example.
typedef void (*DLLFUNCTION1)();
DLLFUNCTION1 dllFunction1;

HMODULE LoadDLL(const char* fileName)
{
   dllHandle =  LoadLibraryA(fileName);

   return dllHandle;
}

int main(int argc, char *argv[])
{
   std::cout << "Loader Process ID is " << GetCurrentProcessId() << "\n";
   dllHandle = LoadDLL(argv[1]);
   if (dllHandle != nullptr)
   {
       cout << "\nDLL called successfully!\n";

       if (argc > 2)
       {
          dllFunction1 = (DLLFUNCTION1)GetProcAddress(dllHandle, argv[2]);
          if (dllFunction1)
          {
              dllFunction1();
              cout << "\nCalled " << argv[2] << " successfully! \n";
          }
          else
          {
              FreeLibrary(dllHandle);
              cout << "\nError in calling " << argv[2] << " does the function exist? \n";
          }
       }
   }
   else
       cout << "DLL could not be called...\n";

   return 0;
}

