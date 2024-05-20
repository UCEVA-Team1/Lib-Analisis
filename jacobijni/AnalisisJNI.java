package jacobijni;
import jacobijni.lib.JacobiCalculator;

public class AnalisisJNI{

	static {

		System.loadLibrary("jacobicalculator");

	}


	public AnalisisJNI(){

		JacobiCalculator calcular = new JacobiCalculator();

		double[] matriz = {4.0, 3.0, -1.0, 2.0, 2.0, -5.0, 1.0, -4.0, 1.0, 2.0, -4.0, -2.0};
		double[] resultado = calcular.calcjacobi(matriz);

		int cont = 0;
		for(int i = 0; i < resultado.length; i++){

			System.out.print(i + " - ");

			if(i < 44){
				if(cont ==3)System.out.println();
				System.out.println(resultado[i]);
			}else{
				System.out.println(resultado[i]);
				System.out.println();
			}


		}


	}


	public static void main(String [] args){

		new AnalisisJNI();

	}

}
