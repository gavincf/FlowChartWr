using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlowChart
{
    public class FileAccess
    {
        /*
         * include sub folder
        * for example
            List<FileInfo> lst = new List<FileInfo>();
            string strPath = @"E:\WORK\g1\北京市\北京市";
            List<FileInfo> lstFiles = getFolderFilesExtAll(strPath, ".asm",lst);
            foreach(FileInfo shpFile in lstFiles)
            {
                label3.Text += shpFile.FullName+"\n";
            }

         */
        public static List<FileInfo> getFolderFileInfoExt(string path, string extName)
        {
            List<FileInfo> lstTemp = new List<FileInfo>();
            try
            {
                //string[] folderList = Directory.GetDirectories(path); //文件夹列表   
                DirectoryInfo curDirectoryInfo = new DirectoryInfo(path);
                FileInfo[] curFolderfileList = curDirectoryInfo.GetFiles();
                //FileInfo[] file = Directory.GetFiles(path); //文件列表   
                if (curFolderfileList.Length != 0 ) //当前目录文件或文件夹不为空                   
                {
                    foreach (FileInfo fileInfo in curFolderfileList) //显示当前目录所有文件   
                    {
                        if (extName.ToLower().IndexOf(fileInfo.Extension.ToLower()) >= 0)
                        {
                            lstTemp.Add(fileInfo);
                        }
                    }
                }
                return lstTemp;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        /*
         *  List<string> listFileContent = FileAccess.StreamGetFile(aFileInfo.FullName,  EncodingUsed);
         */
        public static List<string> StreamGetFile(string path, Encoding encoding) 
        {
            StreamReader steamreader = new StreamReader(path, encoding);
            List<string> listFileContent = new List<string>();//声明一个泛型
            string strTemp;
            while ((strTemp = steamreader.ReadLine()) != null)
            {//read file content to listLinesFileContent
                    listFileContent.Add(strTemp);
            }
            steamreader.Close();
            return listFileContent;
        }

        /*
         * 
         *  List<string> listFileContent = FileAccess.StreamGetFileDelRemark(aFileInfo.FullName,  EncodingUsed,";");
         * 
         */
        public static List<string> StreamGetFileDelRemark(string path, Encoding encoding,string strRemark)
        {
            StreamReader steamreader = new StreamReader(path, encoding);
            List<string> listFileContent = new List<string>();//声明一个泛型
            string strTemp;
            while ((strTemp = steamreader.ReadLine()) != null)
            {//read file content to listLinesFileContent
                int index = strTemp.IndexOf(strRemark);
                if (index >= 0)
                {
                    string strTemp2 = strTemp.Remove(index);//delete remark string
                    listFileContent.Add(strTemp2);
                }
                else
                    listFileContent.Add(strTemp);
            }
            steamreader.Close();
            return listFileContent;
        }
        /*
         * 
         *  List<string> listFileContent = FileAccess.StreamGetFileDelRemark(aFileInfo.FullName,  EncodingUsed,";");
         * 
         */
        public static List<string> StreamGetFileDelRemarkTabUpper(string path, Encoding encoding, string strRemark)
        {
            StreamReader steamreader = new StreamReader(path, encoding);
            List<string> listFileContent = new List<string>();//声明一个泛型
            string strTemp;
            while ((strTemp = steamreader.ReadLine()) != null)
            {//read file content to listLinesFileContent
                int index = strTemp.IndexOf(strRemark);
                if (index >= 0)
                {
                    string strTemp2 = strTemp.Remove(index).Replace('\t',' ');//delete remark string
                    //to upper
                    listFileContent.Add(strTemp2.ToUpper());
                }
                else
                {
                    string strTemp1=strTemp.Replace('\t', ' ');
                    //to upper
                    listFileContent.Add(strTemp1.ToUpper());
                }
            }
            steamreader.Close();
            return listFileContent;
        }

    }
}
