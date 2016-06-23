This project is aimed to offer an example of the used of matlab C interface, and the matlab neural network toolbox.

It complements several posts I published in my blog (in spanish).

1. Backprogation neural network example: https://poncos.wordpress.com/2009/01/15/matlab-ejemplo-backpropagation/
2. Matlab neural network toolbox: https://poncos.wordpress.com/2008/04/14/matlab-toolbox-de-redes-neuronales/ 
3. Matlab interface COM: https://poncos.wordpress.com/2008/08/03/matlab-interfaz-com/

This probject can be used as an example about how to use the C API available with matlab to get access to its toolboxes and environment from an C applicaiton. And it can be used as example about how to apply neural network to machine learning problems, concretely this project applies a backpropagation neural network to recognice handwritten digits from 0 to 9.

This project shows how to apply the typical necessary steps for any system of this characteristics.

1. Data preprocessing. 
2. Neural network application to the preprocessed data.
3. Data postprocessing and results generation.

As aditional technologies, I honestly think that it can be an interesting probject because graphical libraries like libSDL and libTIFF are used to generate a graphical user interface where the user can write with the mouse a digit and the application will preprocess the information to apply the neural network and predict the number.

There are several *.avi videos in the root directory of the project that can be watched to see how the application looks and works.
