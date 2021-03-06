using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Management;
using System.IO;
using static System.Console;



namespace FlowChart
{
    public partial class FormMain : Form
    {
        // public ram define
        public Encoding EncodingUsed = Encoding.GetEncoding("GB2312");
        public string strAsmVersionInfo = Application.ProductVersion.ToString();//"CS_N588HJ 1.2";静态变量

        const bool DEBUG1 = false; // for debug version

        //bios ID table: add all string
        public List<string> listBiosId = new List<string>();
        public List<string> listHarddiskId = new List<string>();

        public string strChip = null;

        public string g_currentDirectory = "";
        public string g_ParrentDirectory = "";
        public string g_DestDirectory = "";
        public string g_ExeFolder = "";


        public Point intWorkArea;

        public void CheckHardwareId()
        {
            //if (DEBUG1 == true)
            //    return;
            //=================================================
            //check  BIOS ID
            ManagementClass mc = new ManagementClass("Win32_BIOS");
            ManagementObjectCollection moc = mc.GetInstances();
            string strBiosID = null;
            foreach (ManagementObject mo in moc)
            {
                strBiosID = mo.Properties["SerialNumber"].Value.ToString();
                break;
            }
            //textBoxID.Text = strBiosID;
            //=================================================
            // checkharddisk
            /*
            ManagementClass mc1 = new ManagementClass("Win32_PhysicalMedia");
            //网上有提到，用Win32_DiskDrive，但是用Win32_DiskDrive获得的硬盘信息中并不包含SerialNumber属性。   
            ManagementObjectCollection moc1 = mc1.GetInstances();
            string strHarkDiskID = null;
            foreach (ManagementObject mo in moc1)
            {
                strHarkDiskID = mo.Properties["SerialNumber"].Value.ToString();
                break;
            }*/

            int biosIdStatus = 0;
            foreach (string str in listBiosId)
            {
                if (strBiosID == str)
                {
                    biosIdStatus = 1;
                    break;
                }
            }
            if (biosIdStatus == 0)
            {
                MessageBox.Show("ID Error!");
            }

            if (biosIdStatus == 0) //|| (harddiskIdStatus == 0))
            {
                System.Environment.Exit(0);
            }
        }


        public FormMain()
        {
            InitializeComponent();

            #region // BIOS ID define
            /*
             * add all BIOS ID
             */
            listBiosId.Add("5430505");//gavin notebook L440
            listBiosId.Add("PK0T95X");//gavin notebook
            //listBiosId.Add("PC0GZ92U");//guang pc
            listBiosId.Add("PC0FUV3K");//zhicheng
            listBiosId.Add("PC0FUV43");//jason
            listBiosId.Add("SS25356597");//kuanglinhai



            //harddisk ID table: add all string
            listHarddiskId.Add("K908T9A2H0GW");//gavin notebook //8EC60785014802083695
            //listHarddiskId.Add("P02646120111");//guang pc
            listHarddiskId.Add("A02007032218");//zhicheng
            listHarddiskId.Add("D203470648       ");//jason
            listHarddiskId.Add("            W2AQ9ZT0");//kuanglinhai

            //----------------------------------------------- add hardware ID end

            CheckHardwareId();
            #endregion

            #region // app version display
            //textBoxVersion.Text = strAsmVersionInfo; //要放在函数中
            this.Text = "FlowChart V" + strAsmVersionInfo;
            #endregion

            #region // get current directory
            //1,get current path
            try
            {
                g_currentDirectory = Directory.GetCurrentDirectory();
            }
            catch (Exception)
            {
                MessageBox.Show("GetCurrentDirectory exception.");
            }

            //2,get parent directory
            try
            {
                g_ParrentDirectory = g_currentDirectory.Substring(0, g_currentDirectory.LastIndexOf('\\'));
                g_ExeFolder = g_currentDirectory.Substring(g_currentDirectory.LastIndexOf('\\') + 1);

            }
            catch (Exception)
            {
                MessageBox.Show("Get DestDirectoryParent exception");
            }
            #endregion
        }


        /*
         * remove all remark in .asm files
         */
        private void removeMarkToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //g_currentDirectory
            //1,check all .asm files in  folder
            DirectoryInfo CurrentDirectoryInfo = new DirectoryInfo(g_currentDirectory);

            List<ConstClass> listStrConst = new List<ConstClass>();

            textBoxLog.AppendText("Del remark and to uppper start:\r\n");
            #region//solve .asm files
            List<FileInfo> lstAsmFileInfos=FileAccess.getFolderFileInfoExt(g_currentDirectory, ".asm");
            foreach (FileInfo aFileInfo in lstAsmFileInfos)
            {
                //get file from info
                List<string> listAsmFileContent = FileAccess.StreamGetFileDelRemarkTabUpper(aFileInfo.FullName,EncodingUsed,";"); //remove remark
                //save asm files.
                StreamWriter streamWrAsm = new StreamWriter(aFileInfo.FullName, false, EncodingUsed);
                foreach (string s in listAsmFileContent)
                    streamWrAsm.WriteLine(s);
                streamWrAsm.Close();
            }
            #endregion

            #region//rolve .h files
            List<FileInfo> lstHFileInfos = FileAccess.getFolderFileInfoExt(g_currentDirectory, ".h");
            foreach (FileInfo aFileInfoH in lstHFileInfos)
            {
                //get file from info
                List<string> listHFileContent = FileAccess.StreamGetFileDelRemarkTabUpper(aFileInfoH.FullName, EncodingUsed,";"); //remove remark
                //save asm files.
                StreamWriter streamWrH = new StreamWriter(aFileInfoH.FullName, false, EncodingUsed); //rewrite .H file
                foreach (string str in listHFileContent)
                {//get const
                    streamWrH.WriteLine(str);
                }
                streamWrH.Close();
            }
            #endregion

            #region//conbine to one list
            List<FileInfo> allFileInfo = lstHFileInfos;
            foreach (FileInfo aFileInfo in lstAsmFileInfos)
            {
                allFileInfo.Add(aFileInfo);
            }
            #endregion
            #region//1,get .IF / .IFDEF CONST
            foreach (FileInfo aFileInfo in allFileInfo)
            {//all
                //get file from info
                List<string> listFileContent = FileAccess.StreamGetFile(aFileInfo.FullName, EncodingUsed);

                List<ConstClass> ListStrConst = new List<ConstClass>();

                for(int listFileContentLine=0; listFileContentLine< listFileContent.Count; listFileContentLine++)
                {
                    int index1 = listFileContent[listFileContentLine].IndexOf(".IFDEF");
                    int index2 = listFileContent[listFileContentLine].IndexOf(".IF");
                    if (index1 >= 0)
                    {

                    }
                    else if (index2 >= 0)
                    {

                    }

                }
                //foreach (string str in listFileContent){}


            }
            #endregion
            #region//2,find .IF / .IFDEF CONST value
            foreach (FileInfo aFileInfo in allFileInfo)
            {//all

                //get file from info
                List<string> listFileContent = FileAccess.StreamGetFile(aFileInfo.FullName, EncodingUsed);

                ConstClass StrConstTemp = new ConstClass(null, null, 0);

                foreach (string str in listFileContent)
                {

                }
            }
            #endregion
            #region//3.delete .IF / .IFDEF string
            foreach (FileInfo aFileInfo in allFileInfo)
            {//all

                //get file from info
                List<string> listFileContent = FileAccess.StreamGetFile(aFileInfo.FullName, EncodingUsed);

                ConstClass StrConstTemp = new ConstClass(null, null, 0);

                foreach (string str in listFileContent)
                {

                }
            }
            #endregion
            #region //4.find all const define
            foreach (FileInfo aFileInfo in allFileInfo)
            {//all
                //get file from info
                List<string> listFileContent = FileAccess.StreamGetFile(aFileInfo.FullName, EncodingUsed);
                ConstClass StrConstTemp = new ConstClass(null, null, 0);
                foreach (string str in listFileContent)
                {//get const
                    int index0 = str.IndexOf(" EQU ");
                    if (index0 >= 0)
                    {
                        string[] sArray = str.Split(' ');
                        int intStep = 0;
                        for (int strIndex = 0; strIndex < sArray.Length; strIndex++)
                        {
                            switch (intStep)
                            {
                                case 0://get const
                                    if (sArray[strIndex] != " ")
                                    {
                                        intStep++;
                                        StrConstTemp.constStr = sArray[strIndex];
                                    }
                                    break;
                                case 1:
                                    if (sArray[strIndex] == "EQU")
                                    {
                                        intStep++;
                                    }
                                    break;
                                case 2:
                                    if (sArray[strIndex] != " ")
                                    {
                                        StrConstTemp.constEquStr = sArray[strIndex];
                                        intStep++;
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        if (intStep == 3)
                        {
                            listStrConst.Add(StrConstTemp);
                        }
                    }
                }
            }
            #endregion
            #region//save to .txt
            StreamWriter streamWrConst = new StreamWriter(g_currentDirectory + "\\All const define.txt", false, EncodingUsed); //rewrite .H file
            foreach (ConstClass constClassTemp in listStrConst)
            {//get const
                streamWrConst.WriteLine(constClassTemp.constStr + "\t" + constClassTemp.constEquStr);
            }
            streamWrConst.Close();
            #endregion

            textBoxLog.AppendText("Del remark and to upper end.\r\n");

        }

        /*
         * menu: File/Exit
         */
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //this.Close();
            Application.Exit();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //OpenFileDialog();
        }

        private void newFileToolStripMenuItem_Click(object sender, EventArgs e)
        {//create new form

            WorkForm newWorkForm1 = new WorkForm(this);
            newWorkForm1.Show();

        }
				
        /*
        #region//事件处理程序
        static void newform1_paint(object sender, PaintEventArgs e)
        {
            Form frm = (Form)sender;
            Graphics g = e.Graphics;
            Rectangle rt = e.ClipRectangle;
            g.Clear(Color.Black);
            rt.Width = 100;
            rt.Height = 100;

            g.DrawString("Hello Word", frm.Font, Brushes.White, new Point(20, 20));
        }
        #endregion
        */
    }
}
