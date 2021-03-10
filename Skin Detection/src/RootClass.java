
public class RootClass {
	
	public RootClass() {
		//probabilitiesOfPixels();
		takeInput();
	}
	
	private void probabilitiesOfPixels() {
		Image img = new Image();
		img.readImages(87);
		img.calculateProbability();
	}
	
	private void takeInput() {
		new IO();
	}
	
}