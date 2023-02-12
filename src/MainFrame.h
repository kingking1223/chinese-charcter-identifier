#pragma once
#include <wx/wx.h>
 
class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
    private:
        void OnPaint(wxPaintEvent& event);
        void OnMouseLeftDown(wxMouseEvent& event);
        void OnMouseLeftUp(wxMouseEvent& event);
        void OnMouseMove(wxMouseEvent& event);

        std::vector<wxPoint> m_points;
        bool m_mouseLeftDown;
        wxRect m_drawingArea;
};