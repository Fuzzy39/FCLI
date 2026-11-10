#include <Engine.h>

class ExampleCLI : public cli::Engine
{
public:
    ExampleCLI(std::istream& input, std::ostream& output)
    {
        // Adding a command with no arguments.
        addCommand(nullptr, "about")
            ->setDescription("about this program")
            ->setImplementation(COMMAND
            {
                out << "FCLI Example.\nDemonstrates the functionality of FCLI.\
                \nThat's not enough text, though, so here's some more.\n";
                return true;
            });

        // demonstrating a command with arguments.
        addCommand(nullptr, "add")
            ->setDescription("Add two numbers.")
            ->addArgument("Term 1", "The first number to add.", cli::builtins::Types::DOUBLE) // FCLI has some built in types, but you can extend the ArgumentType class and add your own.
            ->addArgument("Term 2", "The second number to add.", cli::builtins::Types::DOUBLE)
            ->setImplementation(COMMAND
            {
                double Term1 = *static_cast<double*>(args["Term 1"]); // FCLI handles argument checking for you
                double Term2 = *static_cast<double*>(args["Term 2"]);
                out << Term1 <<" + "<< Term2 <<" = "<< (Term1+Term2)<<"\n";
                return true; 
            });
        

        // commands can be grouped
        auto test = addCommandGroup(nullptr, "test")
            ->setDescription("Demonstrate cli functionality.\nSeriously, just a test. I was in fact testing you.");
        
        
        // adding a command with a variadic argument
        addCommand(test, "sum")
            ->setDescription("sums all of its arguments.\nI mean, checks out, right?")
            ->addArgument("Term 1", "The first term to add.", cli::builtins::Types::DOUBLE)
            ->addVariadicArgument("Term ...", "Additional terms to add.", cli::builtins::Types::DOUBLE)
            ->setImplementation(COMMAND
            {
                double sum = *static_cast<double*>(args["Term 1"]);
                std::vector<void*>* arguments = static_cast<std::vector<void*>*>(args["Term ..."]);

                for(void* arg : *arguments)
                {
                    sum += *static_cast<double*>(arg);
                }

                out<<"The sum is: "<<sum<<".\n";
                return true; 
            });
            
        // Optional argument
        addCommand(test, "repeat")
            ->setDescription("Repeats it's first argument as many times as its second."
                                "\nIf the repeat count isn't provided, repeats twice.")
            ->addArgument("Word", "The word to repeat.", cli::builtins::Types::TOKEN)
            ->addOptionalArgument("Repeat Count", "The number of times to repeat word. Two is the default.",
                                    cli::builtins::Types::INT)
            ->setImplementation(COMMAND
            {
                std::string* word = static_cast<std::string*>(args["Word"]);
                
                int* repeats = static_cast<int*>(args["Repeat Count"]);
                int repeatCount = 2;
                if(repeats != nullptr){ repeatCount = *repeats; }

                for(int i = 0; i<repeatCount; i++)
                {
                    out<<*word<<" ";
                }

                out<<"\n";
                return true; 
            });
        

     
    }
  

};
