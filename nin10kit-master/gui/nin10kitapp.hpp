#ifndef NIN10KITAPP_HPP
#define NIN10KITAPP_HPP

#include "nin10app.hpp"
#include "nin10kit.hpp"

class Nin10KitApp : public Nin10App
{
    public:
        wxFrame* OnInitFrame() override
        {
            return new Nin10KitFrame();
        }
        void OnInitCmdLine(wxCmdLineParser& parser) override;
        bool OnCmdLineParsed(wxCmdLineParser& parser) override;
};

DECLARE_APP(Nin10KitApp);

#endif

