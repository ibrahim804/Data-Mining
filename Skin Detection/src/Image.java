import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import javax.imageio.ImageIO;

public class Image {

	private String imagePrefix = "C:\\Users\\the ibrahim\\eclipse-workspace\\Skin Detection\\image\\image (", imageSuffix = ").jpg";
	private String maskPrefix = "C:\\Users\\the ibrahim\\eclipse-workspace\\Skin Detection\\mask\\mask (", maskSuffix = ").png";
	private BufferedImage image =null , mask = null;
	private File file1 = null, file2 = null;

	private int [][][] rgbSkin = new int [256][256][256];
	private int [][][] rgbNonSkin = new int [256][256][256];
	
	public void readImages(int totalInput) {
		for(int i=1; i<=totalInput; i++) {
			nthImageOpen(i);
			nthMaskOpen(i);
			calculateRGB();
		}
	}
	
	private void nthImageOpen(int i) {
		try {																
			file1 = new File(imagePrefix+String.valueOf(i)+imageSuffix);
			image = ImageIO.read(file1);
		} catch (Exception e) {
			System.out.println("image "+i+" can't open");
		}
	}
	
	private void nthMaskOpen(int i) {
		try {																
			file2 = new File(maskPrefix+String.valueOf(i)+maskSuffix);
			mask = ImageIO.read(file2);
		} catch (Exception e) {
			System.out.println("mask "+i+" can't open");
		}
	}
	
	private void calculateRGB() {
		
		int height = image.getHeight();
		int width = image.getWidth();
		
		for(int i=0; i<height; i++) {
			
			for(int k=0; k<width; k++) {
				
				int rgbValueOfImage = image.getRGB(k, i);
				int rgbValueOfMask = mask.getRGB(k, i);
				
				Color c = new Color(rgbValueOfImage);
				
				int rI = c.getRed();
				int gI = c.getGreen();
				int bI = c.getBlue();
				
				c = new Color(rgbValueOfMask);
				
				int rM = c.getRed();
				int gM = c.getGreen();
				int bM = c.getBlue();
				
				if(rM >=200 && gM >=200 && bM >= 200) rgbSkin[rI][gI][bI]++;
				else rgbNonSkin[rI][gI][bI]++;
				
			}	
		}
	}
	
	public void calculateProbability() {
		
		try {
			
			BufferedWriter bw = new BufferedWriter(new FileWriter("data.txt"));
			
			for(int i=0; i<255; i++) {
				for(int j=0; j<255; j++) {
					for(int k=0; k<255; k++) {
						
						double probability = 0;
						double XplusY = rgbSkin[i][j][k]+rgbNonSkin[i][j][k];
						
						if(XplusY != 0) {
							probability = (double)rgbSkin[i][j][k]/XplusY;
						}
						
						bw.write(String.valueOf(probability)+"\n");
					}
				}
			}
			
			bw.close();
			
		} catch (Exception e) {
			System.out.println("Error in writing file.");
		}
	}
	

}
