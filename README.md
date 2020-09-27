# GitTEest
第一次课实验
1、使用 imread(“文件名”)，读取一张彩色图片。然后将每个像素的r ，g，b值同时改为 （r+g+b）/3，即将3个通道的值统一为相同值，
改为 3个通道的平均值。然后显示图片，观察图片显示的特点，可多测试几张图像。
2、使用 imread(“文件名”，0)，读取一张彩色图片。参数0的意思是，将 读取的图片读取后直接转换为灰度图。 imread(“文件名",0);
然后使用imshow函数显示图像，观察图像，和练习1的结果比较。
3、在练习1的基础上，在处理每个像素的时候加个一个条件。声明一个 uchar变量 uchar threshold =100; 如果average>threshold 
则average=255，否则为0。 然后再把average值赋值给像素的3个通道，并通过imshow函数观察结果， 然后修改threshold值，观察输出结果。
4、读取一张图片，存入mat型变量srcM，然后声明两个mat型数据，命名 为deepMat和shallowMat。分别用深复制和浅复制把srcM的内容赋值给
两个mat。然后用例3中的方法修改srcM的值。观察deepMat和 shallowMat的变化
