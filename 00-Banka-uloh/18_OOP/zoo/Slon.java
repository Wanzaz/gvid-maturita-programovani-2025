package zoo;

public class Slon extends Zvire {
	public Slon(String druh, String jmeno, int vek) {
		super(druh, jmeno, vek);
	}

	@Override
	public void zvuk() {
		System.out.println("Stříká vodu chobotem: PFFFFFF!");
	}
}
