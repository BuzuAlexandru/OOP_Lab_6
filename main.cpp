#include "View.h"
#include "Model.h"
#include "Controller.h"

int main()
{
    Model model;
    View view;
    Controller controller(&view,&model);

    return 0;
}