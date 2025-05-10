package zoo;

public abstract class Zvire {
	private String druh;
	private String jmeno;
	private int vek;

	public Zvire(String druh, String jmeno, int vek) {
		this.druh = druh;
		this.jmeno = jmeno;
		this.vek = vek;
	}

	public String getDruh() {
		return druh;
	}

	public String getJmeno() {
		return jmeno;
	}

	public int getVek() {
		return vek;
	}

	public abstract void zvuk();
}
