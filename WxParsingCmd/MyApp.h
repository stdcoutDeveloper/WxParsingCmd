#pragma once

#include "pch.h"
#include <wx/cmdline.h>
#include "Res/w.xpm"

namespace WxParsingCmd
{
    /**
     * \brief
     * reference: https://docs.wxwidgets.org/3.0/cmdline_8h.html#ae57f6ef76d2377ad95dbc431dee3e969
     * wxCMD_LINE_SWITCH: A boolean argument of the program
     * wxCMD_LINE_OPTION_MANDATORY: This option must be given
     * wxCMD_LINE_PARAM_OPTIONAL: The parameter may be omitted
     * wxCMD_LINE_NONE: terminate the list
     */
    static const wxCmdLineEntryDesc cmdLineDesc[] =
    {
        {
            wxCMD_LINE_SWITCH, "h", "help", "displays help on the command line parameters", wxCMD_LINE_VAL_NONE,
            wxCMD_LINE_OPTION_HELP
        },
        {wxCMD_LINE_SWITCH, "t", "test", "test switch", wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_MANDATORY},
        {wxCMD_LINE_SWITCH, "s", "silent", "disables the GUI"},
        {wxCMD_LINE_NONE}
    };

    class MyApp : public wxApp
    {
    public:

        // from wxApp
        bool OnInit() override
        {
            // call default behaviour (mandatory)
            if (!wxApp::OnInit())
                return false;

            // some application-dependent treatments...

            // Show the frame
            wxFrame* frame = new wxFrame(static_cast<wxFrame*>(nullptr), -1, _T("Hello wxWidgets World"));
            frame->SetIcon(w_xpm);
            frame->CreateStatusBar();
            frame->SetStatusText(_T("Hello World"));

            //if(!is_silent_mode)
            frame->Show(TRUE);

            SetTopWindow(frame);
            return true;
        }

        int OnExit() override
        {
            // clean up
            return 0;
        }

        int OnRun() override
        {
            int exitcode = wxApp::OnRun();
            //wxTheClipboard->Flush();
            if (exitcode != 0)
                return exitcode;
        }

        void OnInitCmdLine(wxCmdLineParser& parser) override
        {
            parser.SetDesc(cmdLineDesc);
            // must refuse '/' as parameter starter or cannot use "/path" style paths
            parser.SetSwitchChars(wxT("-"));
        }

        bool OnCmdLineParsed(wxCmdLineParser& parser) override
        {
            is_silent_mode = parser.Found(wxT("s"));

            // to get at your unnamed parameters use
            wxArrayString files;
            for (int i = 0; i < parser.GetParamCount(); i++)
            {
                files.Add(parser.GetParam(i));
            }

            // and other command line parameters

            // then do what you need with them.

            return true;
        }

    private:
        bool is_silent_mode = false;
    };
}
