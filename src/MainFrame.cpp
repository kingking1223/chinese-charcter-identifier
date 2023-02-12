#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/radiobox.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title), m_mouseDown(false) {
    // wxPanel* panel = new wxPanel(this);

    // wxButton* button = new wxButton(panel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 35));

    // wxCheckBox* checkBox = new wxCheckBox(panel, wxID_ANY, "Check", wxPoint(550, 50), wxDefaultSize, wxCHK_3STATE | wxCHK_ALLOW_3RD_STATE_FOR_USER);

    // wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, "Text", wxPoint(150, 200));

    // wxTextCtrl* textCtrl = new wxTextCtrl(panel, wxID_ANY, "Editable Text", wxPoint(550, 200), wxSize(200, -1));

    // wxSlider* slider = new wxSlider(panel, wxID_ANY, 25, 0, 100, wxPoint(150, 350), wxSize(200, -1), wxSL_VALUE_LABEL);

    // wxGauge* gauge = new wxGauge(panel, wxID_ANY, 100, wxPoint(550, 350), wxSize(200, -1));
    // gauge->SetValue(50);

    // wxArrayString choices;
    // choices.Add("Item A");
    // choices.Add("Item B");
    // choices.Add("Item C");
    // choices.Add("Item D");

    // wxChoice* choice = new wxChoice(panel, wxID_ANY, wxPoint(150, 500), wxSize(100, -1), choices);
    // choice->Select(0);

    // // wxSpinCtrl* spinCtrl = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(550, 500), wxSize(100, -1));

    // wxListBox* listBox = new wxListBox(panel, wxID_ANY, wxPoint(550, 500), wxSize(100, -1), choices);

    // wxRadioBox* radioBox = new wxRadioBox(panel, wxID_ANY, "RadioBox", wxPoint(150, 650), wxDefaultSize, choices);

    m_drawingArea = wxRect(72, 72, 348, 348);
    Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::OnPaint));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MainFrame::OnMouseLeftDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnMouseLeftUp));
    Connect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::OnMouseMove));

    m_displayArea = wxRect(m_drawingArea.GetRight() + 72, 72, 348, 348);
    m_bitmap = wxBitmap(64, 64);
    m_displayMemoryDC.SelectObject(m_bitmap);
    m_displayMemoryDC.SetPen(wxPen(wxColour("WHITE"), 2));
}

void MainFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    wxPen pen(*wxWHITE, 2);
    dc.SetPen(pen);
    dc.SetBrush(wxBrush(wxColour("#101010")));

    dc.DrawRectangle(m_drawingArea);

    wxMemoryDC displayMemoryDC;
    displayMemoryDC.SelectObject(m_bitmap);

    displayMemoryDC.SetBackground(*wxBLACK_BRUSH);
    displayMemoryDC.Clear();

    wxImage image = m_bitmap.ConvertToImage();
    image.Rescale(348, 348);
    wxBitmap resizedBitmap(image);

    dc.DrawBitmap(resizedBitmap, m_displayArea.GetLeft(), m_displayArea.GetTop());

    if (line.size() >= 2)
    {
        dc.DrawLines(line.size(), &line[0], m_drawingArea.GetLeft(), m_drawingArea.GetTop());
    }

    for (const auto &line : m_lines)
    {
        if (line.size() >= 2)
        {
            dc.DrawLines(line.size(), &line[0]);
        }
    }
}

void MainFrame::OnMouseLeftDown(wxMouseEvent& event)
{
    if (m_drawingArea.Contains(event.GetPosition()))
    {
        m_points.clear();
        m_points.push_back(event.GetPosition() - wxPoint(m_drawingArea.x, m_drawingArea.y) + wxPoint(72, 72));
        m_mouseLeftDown = true;
    }
}

void MainFrame::OnMouseLeftUp(wxMouseEvent& event)
{
    if (m_mouseLeftDown)
    {
        m_mouseLeftDown = false;
        if (m_points.size() >= 2)
        {
            m_lines.push_back(m_points);
            m_points.clear();
        }

        wxClientDC dc(this);
        dc.SetPen(wxPen(*wxWHITE, 3));
        dc.SetBrush(*wxWHITE_BRUSH);
        dc.DrawLines(m_lines.back().size(), &m_lines.back()[0]);
    }
}

void MainFrame::OnMouseMove(wxMouseEvent& event)
{
    if (m_mouseLeftDown)
    {
        wxPoint point = event.GetPosition() + wxPoint(72, 72) - wxPoint(m_drawingArea.x, m_drawingArea.y);
        if (m_drawingArea.Contains(point - wxPoint(72, 72) + wxPoint(m_drawingArea.x, m_drawingArea.y)))
        {
            m_points.push_back(point);
            m_lines.push_back(m_points);
            Refresh();
        }
        else
        {
            m_mouseLeftDown = false;
        }
    }
}