using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FlowChart
{
    class WorkForm:Form
    {

        // Sets g to a graphics object representing the drawing surface of the
        // control or form g is a member of.
        #region //PageForm graphic define
        static Graphics workFormGraphics;
        static Point workFormPointStart = new Point(0, 0);
        static Point workFormPointEnd = new Point(0, 0);
        static int workFormDrawX1 = new int();
        static int workFormDrawY1 = new int();
        static int workFormDrawX2 = new int();
        static int workFormDrawY2 = new int();
        static Pen workFormPen = new Pen(Color.FromArgb(255, 255, 0, 0), 3);
        private Button buttonTest;
        static int workFormMouseFlag = 0;//1:pressed,0:release
        #endregion

        #region // structure
        public WorkForm()
        {//structure
            Text = "通过继承创建窗体";
            BackColor = Color.Black;

        }
        public WorkForm(Form baseForm)
        {//structure

            int intEdgeWidth= 2;
            int intMenuHeight = 55;
            StartPosition = FormStartPosition.Manual;
            //Location = baseForm.Location;

            this.Text = "通过继承创建窗体";
            this.BackColor = Color.White;
            this.Top = baseForm.Location.Y+ intMenuHeight;
            this.Left = baseForm.Location.X+ intEdgeWidth;
            this.Width = baseForm.Width- intEdgeWidth * 2;
            this.Height = baseForm.Height- intMenuHeight - intEdgeWidth;
            this.Invalidate();
            workFormGraphics = this.CreateGraphics();

        }
        #endregion

        protected override void OnPaint(PaintEventArgs e)
        {
            //Graphics g = e.Graphics;
            //workFormGraphics = this.CreateGraphics();
            //g.DrawString("Hello World", Font, Brushes.Yellow, new Point(0, 0));
            base.OnPaint(e);

        }

        /*
         * will be called
         */
        private void InitializeComponent()
        {
            this.buttonTest = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonTest
            // 
            this.buttonTest.Location = new System.Drawing.Point(424, 29);
            this.buttonTest.Name = "buttonTest";
            this.buttonTest.Size = new System.Drawing.Size(75, 23);
            this.buttonTest.TabIndex = 0;
            this.buttonTest.Text = "button1";
            this.buttonTest.UseVisualStyleBackColor = true;
            this.buttonTest.Click += new System.EventHandler(this.buttonTest_Click);
            // 
            // WorkForm
            // 
            this.ClientSize = new System.Drawing.Size(557, 261);
            this.Controls.Add(this.buttonTest);
            this.Name = "WorkForm";
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.WorkForm_MouseDown);
            this.MouseMove += new System.Windows.Forms.MouseEventHandler(this.WorkForm_MouseMove);
            this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.WorkForm_MouseUp);
            this.ResumeLayout(false);

        }

        public void drawDot()
        {
            workFormGraphics.DrawLine(workFormPen, workFormDrawX1, workFormDrawY1, workFormDrawX2 + 1, workFormDrawY1);
            //form1Graphics.DrawLine(form1Pen, g_form1PointStart, g_form1PointEnd);
        }

        private void WorkForm_MouseDown(object sender, MouseEventArgs e)
        {
            workFormMouseFlag = 1;
            workFormDrawX1 = workFormDrawX2 = e.X;
            workFormDrawY1 = workFormDrawY2 = e.Y;
            //g_form1PointStart = g_form1PointEnd = Form1.MousePosition.Offset

            drawDot();

        }

        private void WorkForm_MouseMove(object sender, MouseEventArgs e)
        {
            if (workFormMouseFlag == 1)
            {
                //if((g_form1DrawX1!= Form1.MousePosition.X) || (g_form1DrawY1 != Form1.MousePosition.Y))
                if ((workFormDrawX1 != e.X) || (workFormDrawY1 != e.Y))
                {
                    workFormDrawX1 = workFormDrawX2 = e.X;
                    workFormDrawY1 = workFormDrawY2 = e.Y;

                    drawDot();

                }
            }

        }

        private void WorkForm_MouseUp(object sender, MouseEventArgs e)
        {
            workFormMouseFlag = 0;

        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            workFormMouseFlag = 0;
        }
    }
}
