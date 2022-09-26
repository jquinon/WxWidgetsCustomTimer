#include <myframe.hpp>
#include <string> 


MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Timer", wxDefaultPosition, wxSize(500,500))
{
    this->minutes = 0;
    this->seconds = 0;
    this->timerActive = false;

    

    //Vertical Sizer
    wxBoxSizer *timer_sizer = new wxBoxSizer( wxVERTICAL );
        //Static Text Display
        wxBoxSizer *text_sizer = new wxBoxSizer (wxHORIZONTAL);
            this->timeText = new wxStaticText(this, ID_Time_Text, "00:00", wxDefaultPosition, wxSize(350, 100), wxALIGN_CENTRE_HORIZONTAL);
            wxFont f = this->timeText->GetFont();
            f.SetPointSize(20);
            this->timeText->SetFont(f);
        text_sizer->Add(this->timeText, 0, wxALIGN_CENTER);

        //Horizontal Sizer
        wxBoxSizer *button_sizer = new wxBoxSizer( wxHORIZONTAL );
            //Toggle Button
            wxButton *ToggleTimerButton = new wxButton(this, ID_Toggle_Button, "Start/Stop", wxDefaultPosition, wxSize(150,50) );
            ToggleTimerButton->Bind(wxEVT_BUTTON, &MyFrame::toggleTimer, this);

            //Reset Button100
            wxButton *ResetButton = new wxButton(this, ID_Reset_Button, "Reset", wxDefaultPosition, wxSize(150,50) );
            ResetButton->Bind(wxEVT_BUTTON, &MyFrame::reset, this);

        button_sizer->Add(ToggleTimerButton, 0, wxALIGN_CENTER);
        button_sizer->Add(ResetButton, 0, wxALIGN_CENTER);

    
    timer_sizer->Add(text_sizer, 0, wxALIGN_CENTER);
    timer_sizer->Add(button_sizer, 0, wxALIGN_CENTER);
    

    SetSizerAndFit(timer_sizer);


    this->customTimer = new CustomTimer(this);
    
}

void MyFrame::toggleTimer(wxCommandEvent& event)
{
    if(this->timerActive){
        //if on turn off
        this->timerActive = false;
        customTimer->Stop();
    }else{
        customTimer->Start(1000);
        this->timerActive = true;
    }
}

void MyFrame::tickSecond(){
    this->seconds += 1;

    if(this->seconds >= 60){
        this->seconds -= 60;
        this->minutes += 1;
    }

    this->timeText->SetLabelText(formatTime(this->minutes, this->seconds));
}

void MyFrame::reset(wxCommandEvent& event){
    this->seconds = 0;
    this->minutes = 0;
    this->timerActive = false;
    this->customTimer->Stop();
    this->timeText->SetLabelText("00:00");
}


MyFrame::CustomTimer::CustomTimer(MyFrame* _mf){
    wxTimer();
    this->mf = _mf;
}

void MyFrame::CustomTimer::Notify(){
    this->mf->tickSecond();
}


std::string MyFrame::formatTime(int minutes, int seconds){
    std::string time = "";

    if(minutes < 10){
        time += "0";
    }
    time += std::to_string(minutes);

    time += ":";

    if(seconds < 10){
        time += "0";
    }
    time += std::to_string(seconds);

    return time;
}
