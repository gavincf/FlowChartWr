using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FlowChart
{
	public class ConstClass
	{
		public string constStr = null;
        public string constEquStr = null;
        public int constEquInt = 0;//dummy

        public ConstClass(string str1,string str2,int int1)
        {
            this.constStr = str1;
            this.constEquStr = str2;
            this.constEquInt = int1;
        }
        /*
        public IEnumerator GetEnumerator()
        {

            return ((IEnumerable)(constStr+" "+ constEquStr)).GetEnumerator();
        }*/

    }
}