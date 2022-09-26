#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <myframe.hpp>
 
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 

wxIMPLEMENT_APP(MyApp);
