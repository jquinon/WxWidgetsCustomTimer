#ifndef MYFRAME_H
#define MYFRAME_H

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string>

enum
{
    ID_Hello = 1,
    ID_Toggle_Button = 2,
    ID_Reset_Button = 3,
    ID_Time_Text = 4,
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    static std::string formatTime(int minutes, int seconds);
    
private:

    class CustomTimer : public wxTimer{
        public :
            CustomTimer(MyFrame* _mf);

            void Notify();

        private:
            MyFrame* mf;
    };
    
    int minutes;
    int seconds;
    bool timerActive;
    

    wxStaticText* timeText;
    CustomTimer* customTimer;
    

    void OnClick(wxCommandEvent& event);
    void toggleTimer(wxCommandEvent& event);
    void reset(wxCommandEvent& event);
    

    void tickSecond();
};

#endif