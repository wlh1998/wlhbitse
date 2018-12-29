using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace sudokugui
{
    
    public partial class Form1 : Form
    {
        private char[,] data;
        public bool Sudokucheck()
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    data[i, j] = (char)dataGridView1.Rows[i].Cells[j].Value.ToString().ToCharArray()[0];
                }
            }
            int rowsum, colsum;
            for (int i = 0; i < 9; i++)
            {
                rowsum = 0;
                colsum = 0;
                for (int j = 0; j < 9; j++)
                {
                    if (data[i, j] == '0')
                    {
                        return false;
                    }
                    rowsum += data[i, j]-'0';
                    colsum += data[j, i]-'0';
                }
                if(rowsum != 45|| colsum != 45)
                {
                    return false;
                }
            }
                int starti = 0;
                int startj = 0;
            for (int i = 0; i < 9; i++)
            {
                starti = (i*3) % 9;
                startj = (i/3)*3;
                int cellsum = 0;

                for (int j = 0; j < 3; j++)
                {
                    for(int k = 0; k < 3; k++)
                    {
                        cellsum += data[starti+j,startj+k]-'0';
                    }
                }
                if (cellsum != 45)
                {
                    return false;
                }
            }

            return true;
        }
        public void Newsudoku()
        {
            string srank = "123456789";
            char[] rank = srank.ToCharArray();
            string sshift = "036147258";
            char[] shift = sshift.ToCharArray();
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    data[i, j] = rank[(i+shift[j])%9];
                    
                }
            }
        }
        public void Newsudokuproblem()
        {
            Newsudoku();
            //mask true 保留
            bool[,] mask = new bool[9,9];
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {

                    if ((i + j) % 3 == 0)
                    {
                        mask[i, j] = false;
                    }
                    else
                    {
                        mask[i, j] = true;
                    }
                }
            }
            Random ran = new Random();
            int blanknum = ran.Next(31-27, 59-27);
            int randi = ran.Next(0, 9);
            int randj = ran.Next(0, 9);

            for (int i = 0; i < blanknum; i++)
            {
                while(mask[randi,randj] == false)
                {
                    randi = ran.Next(0, 9);
                    randj = ran.Next(0, 9);
                }
                mask[randi, randj] = false;
            }
            for (int i =0; i < 9; i++)
            {
                for(int j = 0; j < 9; j++)
                {
                    if(mask[i,j] == false)
                    {
                        data[i, j] = '0';
                    }
                }
            }
        } 
        public Form1()
        {
            InitializeComponent();
            data = new char[9, 9];
            dataGridView1.AllowUserToAddRows = false;
            dataGridView1.RowHeadersVisible = false;
            dataGridView1.ColumnHeadersVisible = false;
            this.Text = "sudoku game";

        }

        private void button2_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            Newsudokuproblem();

            for (int i = 0; i < 9; i++)
            {
                dataGridView1.Rows.Add();
                for (int j = 0; j < 9; j++)
                {
                    dataGridView1.Rows[i].Cells[j].Value = data[i, j];
                    if(data[i,j] == '0')
                    {
                        dataGridView1.Rows[i].Cells[j].ReadOnly = false;
                        dataGridView1.Rows[i].Cells[j].Style.Font = new Font("Tahoma",10,FontStyle.Bold);
                    }
                    else
                    {
                        dataGridView1.Rows[i].Cells[j].ReadOnly = true;
                        dataGridView1.Rows[i].Cells[j].Style.Font = new Font("Tahoma", 10, FontStyle.Regular);
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (Sudokucheck())
            {
                label1.Text = "结果正确";
            }
            else
            {
                label1.Text = "结果错误";
            }
        }
    }
 
}
