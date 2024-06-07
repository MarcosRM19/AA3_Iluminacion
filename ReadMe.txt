1.
Tener en cuenta que he decidio incorporar un suelo la cual tiene ciertas diferencias a los modelos normales, la más importante es que este tiene su propio Fragment Shader ya
quiero que el suelo sea tintado por el ambient color de las orbitas para mostrar que la interpolacion se esta ejecutando bien a la vez que es afectado por la luz de estas,
pero no quiero que la linterna afecte a este ya que al ser un modelo tan simple genera pequeños problemas al iluminarla con la linterna, dejando eso exclusivo de los modelos

El suelo a la vez tapa la orbita inferior de el sol y la luna pero realmente si esta realizando la orbita, si se quiere comprobra que se esta efectuando se puede comentar la 
línia "floor->Update(_dt)" que se encuentra en el update del ObjectManager para que no se renderize y poder ver toda la orbita

2.
Se que me comentaste que tanto el sol como la luna no tienen que tener un shader pero he decido incorporarles uno que simplemente cambia el color de estas primitivas al escogido

3.
Parte del código se ha realizo grácias a busqueda por internet, destcando las partes de código:

	-Todo el InputManager (sobretodo el funcionamiento de los CallBacks)
	-Pequeñas funciones de los shaders como "mix" para calcular la interpolacion o "smoothstep" para la linterna
	-Las dos últimas líneas del shader relacionada a la linterna (líneas 56 y 58) del MyFirstFragmentShader.glsl
	-El cáculo del alpha value dependiendo del angulo
