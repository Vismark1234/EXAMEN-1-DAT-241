using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Bordes
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
                openFileDialog.Filter = "Imagenes PNG (*.png)|*.png|Imagenes JPG (*.jpg;*.jpeg)|*.jpg;*.jpeg|Todos los archivos (*.*)|*.*";

                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    string filePath = openFileDialog.FileName;
                    pictureBox1.Image = Image.FromFile(filePath);
                    pictureBox1.SizeMode = PictureBoxSizeMode.Zoom; // Ajusta la imagen 
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                Bitmap imagenOriginal = new Bitmap(pictureBox1.Image);
                Bitmap imagenBordes = DetectarBordes(imagenOriginal);


                pictureBox2.Image = imagenBordes; 
                pictureBox2.SizeMode = PictureBoxSizeMode.Zoom; // Ajusta la imagen
            }
        }

        private Bitmap DetectarBordes(Bitmap imagenOriginal)
        {
            
            int[,] vecX = new int[,]
            {
                { -1, 0, 1 },
                { -2, 0, 2 },
                { -1, 0, 1 }
            };

            int[,] vecY = new int[,]
            {
                { 1, 2, 1 },
                { 0, 0, 0 },
                { -1, -2, -1 }
            };

            Bitmap imagenBordes = new Bitmap(imagenOriginal.Width, imagenOriginal.Height);

            for (int x = 1; x < imagenOriginal.Width - 1; x++)
            {
                for (int y = 1; y < imagenOriginal.Height - 1; y++)
                {
                    int valorX = 0;
                    int valorY = 0;


                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            Color colorPixel = imagenOriginal.GetPixel(x + i, y + j);
                            int gris = (int)(colorPixel.R * 0.299 + colorPixel.G * 0.587 + colorPixel.B * 0.114);
                            valorX += gris * vecX[i + 1, j + 1];
                            valorY += gris * vecY[i + 1, j + 1];
                        }
                    }

                    int magnitud = (int)Math.Sqrt(valorX * valorX + valorY * valorY);
                    magnitud = Math.Min(255, Math.Max(0, magnitud)); 

                    imagenBordes.SetPixel(x, y, Color.FromArgb(magnitud, magnitud, magnitud));
                }
            }

            return imagenBordes;
        }

        private void button3_Click(object sender, EventArgs e)
        {   
            pictureBox1.Image = null;  
            pictureBox2.Image = null;   
            return;
        }
    }
}
