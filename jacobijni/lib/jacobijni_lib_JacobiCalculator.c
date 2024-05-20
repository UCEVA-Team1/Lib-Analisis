#include <jni.h>

/*
 * Class:     jacobijni_lib_JacobiCalculator
 * Method:    calcjacobi
 * Signature: ([D)[D
 */
JNIEXPORT jdoubleArray JNICALL Java_jacobijni_lib_JacobiCalculator_calcjacobi
  (JNIEnv *env, jobject obj, jdoubleArray matrizDouble){


	jdouble *matriz = (*env)->GetDoubleArrayElements(env, matrizDouble, NULL);

	double resultado[60];  // 15 iteraciones * 3 variables + 15 errores
    int iteraciones = 15;
    int i, j;

    double operacion1[4] = {0};
    double operacion2[4] = {0};
    double operacion3[4] = {0};
    double divisores[3] = {0};
    int pos = 0;

    for (int i = 0; i < 4; i++) {
        if (i == pos) {
            operacion1[pos] = 0;
            divisores[pos] = matriz[i]; // matriz[0] = 4.0
        } else {
            if (i == 3) {
                operacion1[3] = matriz[i]; // matriz[3] = 2.0
            } else {
                operacion1[i] = matriz[i] * -1; // matriz[1] = -3.0, matriz[2] = 1.0
            }
        }
    }

    pos++;

    for (int i = 0; i < 4; i++) {
        if (i == pos) {
            operacion2[pos] = 0;
            divisores[pos] = matriz[i + 4]; // matriz[4] = 2.0
        } else {
            if (i == 3) {
                operacion2[3] = matriz[i + 4]; // matriz[7] = -4.0
            } else {
                operacion2[i] = matriz[i + 4] * -1; // matriz[5] = 5.0, matriz[6] = -1.0
            }
        }
    }

    pos++;

    for (int i = 0; i < 4; i++) {
        if (i == pos) {
            operacion3[pos] = 0;
            divisores[pos] = matriz[i + 8]; // matriz[8] = 1.0
        } else {
            if (i == 3) {
                operacion3[3] = matriz[i + 8]; // matriz[11] = -2.0
            } else {
                operacion3[i] = matriz[i + 8] * -1; // matriz[9] = -2.0, matriz[10] = 4.0
            }
        }
    }


	double x = 0.0, y = 0.0, z = 0.0;
    double Ax = 0.0, Ay = 0.0, Az = 0.0;
    double maxX = 0.0, maxY = 0.0, maxZ = 0.0;
    double maxTotal = 0.0, maxDivi = 0.0;
    int indx = 3;

    resultado[0] = x;
    resultado[1] = y;
    resultado[2] = z;

    for (i = 0; i < iteraciones; i++) {
        Ax = x;
        Ay = y;
        Az = z;

        x = operacion1[3] + (operacion1[1] * Ay) + (operacion1[2] * Az);
        y = operacion2[3] + (operacion2[0] * Ax) + (operacion2[2] * Az);
        z = operacion3[3] + (operacion3[0] * Ax) + (operacion3[1] * Ay);

        x = x / divisores[0];
        y = y / divisores[1];
        z = z / divisores[2];

        resultado[indx] = x;
        resultado[indx + 1] = y;
        resultado[indx + 2] = z;
        indx += 3;
    }

	indx = 3;

    for (i = 0; i < iteraciones; i++) {
        maxX = resultado[indx];
        maxY = resultado[indx + 1];
        maxZ = resultado[indx + 2];

	if(maxX < 0) maxX = maxX*-1;
            if(maxY < 0) maxY = maxY*-1;
            if(maxZ < 0) maxZ = maxZ*-1;


	if(maxX>maxY){
                if(maxX>maxZ){
                    maxDivi = maxX;
                }else{
                    maxDivi = maxZ;
                }
            }else{
                if(maxY>maxZ){
                    maxDivi = maxY;
                }else{
                    maxDivi = maxZ;
                }
            }

        maxX = resultado[indx] - resultado[indx - 3];
        maxY = resultado[indx + 1] - resultado[indx - 2];
        maxZ = resultado[indx + 2] - resultado[indx - 1];

	if(maxX < 0) maxX = maxX*-1;
            if(maxY < 0) maxY = maxY*-1;
            if(maxZ < 0) maxZ = maxZ*-1;

            if(maxX>maxY){
                if(maxX>maxZ){
                    maxTotal = maxX;
                }else{
                    maxTotal = maxZ;
                }
            }else{
                if(maxY>maxZ){
                    maxTotal = maxY;
                }else{
                    maxTotal = maxZ;
                }
            }

	indx += 3;

        resultado[45+i] = maxTotal / maxDivi;
    }

       jdoubleArray resultadoArray = (*env)->NewDoubleArray(env, 60);
       (*env)->SetDoubleArrayRegion(env, resultadoArray, 0, 60, resultado);

	(*env)->ReleaseDoubleArrayElements(env, matrizDouble, matriz, JNI_ABORT);

	return resultadoArray;


}
