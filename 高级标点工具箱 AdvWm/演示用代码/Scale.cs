using System;
using System.Drawing;
using System.Windows.Forms;
using static Triggernometry.RealPlugin;

public class ScaleForm : Form
{
    private TrackBar scaleXTrackBar;
    private TrackBar scaleYTrackBar;
    private Label scaleXLabel;
    private Label scaleYLabel;

    public ScaleForm()
    {
        this.Text = "ScaleX ScaleY 的变化";
        this.Font = new Font("等距更纱黑体 SC", 9.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
        this.Padding = new Padding(10); 
        InitializeComponents();
    }

    private void InitializeComponents()
    {
        scaleXTrackBar = new TrackBar();
        scaleYTrackBar = new TrackBar();

        scaleXTrackBar.Minimum = -300;
        scaleXTrackBar.Maximum = 300;
        scaleXTrackBar.TickStyle = TickStyle.Both;
        scaleXTrackBar.TickFrequency = 100;
        scaleXTrackBar.SmallChange = 5;
        scaleXTrackBar.LargeChange = 100;
        scaleXTrackBar.ValueChanged += TrackBar_ValueChanged;

        scaleYTrackBar.Minimum = -300;
        scaleYTrackBar.Maximum = 300;
        scaleYTrackBar.TickStyle = TickStyle.Both;
        scaleYTrackBar.TickFrequency = 100;
        scaleYTrackBar.SmallChange = 5;
        scaleYTrackBar.LargeChange = 100;
        scaleYTrackBar.ValueChanged += TrackBar_ValueChanged;

        scaleXLabel = new Label { Text = "ScaleX: 0", Dock = DockStyle.Top };
        scaleYLabel = new Label { Text = "ScaleY: 0", Dock = DockStyle.Top };

        this.Controls.Add(scaleYTrackBar);
        this.Controls.Add(scaleYLabel);
        this.Controls.Add(scaleXTrackBar);
        this.Controls.Add(scaleXLabel);

        scaleXTrackBar.Dock = DockStyle.Top;
        scaleYTrackBar.Dock = DockStyle.Top;
        
        scaleXTrackBar.Margin = new Padding(10, 20, 10, 0);
        scaleYTrackBar.Margin = new Padding(10, 20, 10, 0);
    }

    private void TrackBar_ValueChanged(object sender, EventArgs e)
    {
        scaleXLabel.Text = $"ScaleX: {scaleXTrackBar.Value / 100.0:F1}";
        scaleYLabel.Text = $"ScaleY: {scaleYTrackBar.Value / 100.0:F1}";
        var cmd = $@"
           Action: Circle
           Center: 100, 100, 0
           Waymarks: A1D4C3B2
           R: 10
           scaleX: {scaleXTrackBar.Value / 100.0}
           scaleY: {scaleYTrackBar.Value / 100.0}
        ";
        plug.InvokeNamedCallback("AdvWm", cmd);
    }
}

plug.ui.Invoke(() => new ScaleForm().Show());
