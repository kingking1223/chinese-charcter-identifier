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
        void OnClearButtonClick(wxCommandEvent& event);

        std::vector<wxPoint> m_points;
        bool m_mouseLeftDown;
        wxRect m_drawingArea;

        wxRect m_displayArea;
        wxBitmap m_bitmap;
        wxMemoryDC m_displayMemoryDC;

        wxPoint m_lastPoint;
        wxPen m_pen;
        std::vector<std::vector<wxPoint>> m_lines;
        bool m_drawingStarted;
        std::vector<wxPoint> line;

        bool m_mouseDown;

        wxButton* m_clearButton;
};