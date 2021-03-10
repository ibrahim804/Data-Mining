import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Scanner;
import javax.imageio.ImageIO;

public class IO {

	private double threshold = 0.25;
	private double [][][] fileArray = new double [256][256][256]; 
	
	public IO() {
		
		Scanner inp = new Scanner(System.in);
		System.out.print("Enter file name : ");
		String filename = inp.nextLine();
		inp.close();
		readInputWriteToAnother(filename);
		
	}
	
	private void readInputWriteToAnother(String filename) {
		
		retrieveFromFile();
		
		try {
			
			BufferedImage image1 = null, image2 = null;
			File file1 = null, file2 = null;
			
			file1 = new File(filename);
			image1 = ImageIO.read(file1); 
			
			int height = image1.getHeight();
			int width = image1.getWidth();
			
			image2 = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
			file2 = new File(getMaskName(filename));
			
			Color c;
			
			for(int i=0; i<height; i++) { 
				for(int j=0; j<width; j++) {  
					int rgb = image1.getRGB(j, i);
					c = new Color(rgb);
					int r = c.getRed(), g = c.getGreen(), b = c.getBlue();
					if(fileArray[r][g][b]<threshold) {
						r=g=b=0;
					} else {
						r=g=b=255;
					}
					image2.setRGB(j, i, new Color(r,g,b).getRGB());
				}
			}
			
			ImageIO.write(image2, "jpg", file2);
	
		} catch (Exception e) {
			System.out.println("input file can't open.");
		}
	}
	
	private void retrieveFromFile() {
		try {
			BufferedReader br = new BufferedReader(new FileReader("data.txt"));
			for(int i=0; i<255; i++) {
				for(int j=0; j<255; j++) {
					for(int k=0; k<255; k++){
						double val = Double.parseDouble(br.readLine()); 
						fileArray[i][j][k]=val;
					}
				}
			}
			br.close();
		} catch (Exception e) {
			System.out.println("data file can't open");
		}
	}
	
	private String getMaskName(String filename) {
		int len = filename.length();
		String prefix = filename.substring(0, len-4)+"BlackAndWhite";
		String suffix = filename.substring(len-4);								
		return prefix+suffix;
	}
	
}
