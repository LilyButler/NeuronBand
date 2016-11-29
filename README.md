# NeuronBang
This project is about the neural circuits, neuronal conductivity and technologies.
For modeling of neural circuits is advantageous to use the program which was created by the Penn State University.
<div class="sixteen columns"><hr></div>
<pre class="htmlize" id="sample-project">
<h2> NeuronC </h2>
<p>
<img style="-webkit-user-select: none; cursor: zoom-in;" src="http://retina.anatomy.upenn.edu/~rob/spike_gen.png" alt="An array of neurons" title="NeuronC program" align="right" data-canonical-src="http://retina.anatomy.upenn.edu/~rob/spike_gen.png" style="max-width:10%;" width="199" height="199">
NeuronC is computer programm for modeling simulating large neural circuits.
Developed by <a href="http://retina.anatomy.upenn.edu/~rob/"> Robert Smith </a>
</p>
<div class="one-third column"><h3 class="offset-by-one">Installation</h3></div>
<div class="two-thirds column">
      <a name="installayion"></a>
      <ol>
        <li>NeuronC runs under virtually any Unix system, and is currently developed under Linux</li>
        <li><a href="http://vrc.med.upenn.edu/files/nc.tgz">Download</a> the NeuronC</li>
        <li>Unzip the folder and install on you system</li>
      </ol>
</div>
<h3> RUN </h3>
<p>In order to run the calculation necessary to make following adjustments in the program:</p>
<ol>
<li> Open the <span class="string"> "makefile" </span> (for example <kbd> [...nc/src]& vim makefile </kbd> ) </li> 
<li> Change the <kbd> SHELL=/bin/csh </kbd> on <kbd> SHELL=/bin/bash </kbd> make this change to all makefiles program </li>
<li> More please replace the following variables <kbd>CFLAGS = -Ofast</kbd> on <kbd># CFLAGS = -Ofast</kbd>
and <kbd># CFLAGS = -O3</kbd> on <kbd>CFLAGS = -O3 -fPIC</kbd> in all makefiles program
</ol>
