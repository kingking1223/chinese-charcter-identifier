#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/radiobox.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title), m_mouseDown(false) {

    m_drawingArea = wxRect(72, 72, 512, 512);
    Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::OnPaint));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MainFrame::OnMouseLeftDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnMouseLeftUp));
    Connect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::OnMouseMove));

    m_bitmap = wxBitmap(64, 64);
    m_displayMemoryDC.SelectObject(m_bitmap);
    m_displayMemoryDC.SetPen(wxPen(wxColour("WHITE"), 2));

    m_clearButton = new wxButton(this, wxID_ANY, "Clear", wxPoint(620, 80), wxSize(10, 10));
    Connect(m_clearButton->GetId(), wxEVT_BUTTON, wxCommandEventHandler(MainFrame::OnClearButtonClick));
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

    m_clearButton->SetPosition(wxPoint(80, 600));
    m_clearButton->SetSize(wxSize(100, 50));


    // if (line.size() >= 2)
    // {
    //     wxPoint scaledLine[line.size()];
    //     for (size_t i = 0; i < line.size(); i++)
    //     {
    //         scaledLine[i] = line[i] / 8;
    //     }
    //     dc.DrawLines(line.size(), scaledLine, m_drawingArea.GetLeft(), m_drawingArea.GetTop());
    // }

    // for (const auto &line : m_lines)
    // {
    //     if (line.size() >= 2)
    //     {
    //         wxPoint scaledLine[line.size()];
    //         for (size_t i = 0; i < line.size(); i++)
    //         {
    //             scaledLine[i] = line[i] / 8;
    //         }
    //         dc.DrawLines(line.size(), scaledLine);
    //     }
    // }
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
        }

        m_points.clear();

        wxClientDC dc(this);
        dc.SetPen(wxPen(*wxWHITE, 3));
        dc.SetBrush(*wxWHITE_BRUSH);
        for (const auto &line : m_lines)
        {
            if (line.size() >= 2)
            {
                dc.DrawLines(line.size(), &line[0]);
            }
        }
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

            wxClientDC dc(this);
            dc.SetPen(wxPen(*wxWHITE, 3));
            dc.SetBrush(*wxWHITE_BRUSH);
            dc.DrawLine(m_points[m_points.size()-2], m_points[m_points.size()-1]);
        }
        else
        {
            m_mouseLeftDown = false;
        }
    }
}

void MainFrame::OnClearButtonClick(wxCommandEvent& event)
{
    m_lines.clear();
    line.clear();
    m_bitmap = wxBitmap(64, 64);
    m_displayMemoryDC.SelectObject(m_bitmap);
    Refresh();
}