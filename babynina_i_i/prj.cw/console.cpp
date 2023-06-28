#include <iostream>
#include <argParser/argParser.hpp>
#include <QRBeautify.h>
#include <string>

int main(int argc, char** argv) {
	ArgumentParser::ArgParser parser("QRBeautify_TEST");

    // Adding a positional argument for text in QR
    parser.AddStringPositional(1);

    // Adding an argument to generate
    parser.AddStringArgument('t', "text").MultiValue(1).AddDescription("Text that will encodes in qr");

    parser.AddStringArgument('i', "image").AddDescription("Merge QR with existing image");
    parser.AddStringArgument('m', "mode").AddDescription("Desired merging mode: overlay or merge");

    parser.AddStringArgument('h', "heatmap").AddDescription("Encode QR heatmap-like, add param: square or round without flag");

    parser.AddIntArgument('B', "basic").MultiValue(3).AddDescription("Encode QR with solid color, add params withput flags r,g,b and shape with flag");
    parser.AddStringArgument('s', "shape").AddDescription("Parametr for basic generator");

    // Adding an argument to output the contents of the file
    // parser.AddFlag('p', "print").AddDescription("Print the content of the file");
    
    if (parser.Parse(argc, argv) && parser.GetPositionalCount() > 0 && parser.GetArgumentCount("text") > 0) {
    	std::string text = "";
		for (int i = 0; i < parser.GetArgumentCount("text"); i++) {
            text += parser.GetStringValue("text", i) + " ";
        }
        text.resize(text.size() - 1);
		QrBeautifier qr = QrBeautifier(text.c_str());

		if (parser.GetArgumentCount("image") > 0) {
            std::string input_image_path = "";
            input_image_path += parser.GetStringValue("image", 0) + " ";
            input_image_path.resize(input_image_path.size() - 1);

            if (parser.GetArgumentCount("mode") > 0) {
            	std::string merge_mode = "";
                merge_mode += parser.GetStringValue("mode", 0) + " ";
                merge_mode.resize(merge_mode.size() - 1);

                if (merge_mode == "overlay") {
		            qr.overlayImageWithQR(input_image_path.c_str());
		        } else {
		            qr.overlayQRWithImage(input_image_path.c_str());
		        }
		        qr.saveImage();

            }

        }
        
        if (parser.GetArgumentCount("heatmap") > 0) {
        	std::string h_shape = "";
            h_shape += parser.GetStringValue("heatmap", 0) + " ";
            h_shape.resize(h_shape.size() - 1);
	        qr.heatmap((h_shape == "square") ? AnchorShape::Square : AnchorShape::Round);
	        qr.saveImage();
	    }

	    if (parser.GetArgumentCount("basic") > 0) {
	        int r = parser.GetIntValue("basic", 0);
	        int g = parser.GetIntValue("basic", 1);
	        int b = parser.GetIntValue("basic", 2);
	        if (parser.GetArgumentCount("shape") > 0) {
	        	std::string shape = "";
	            shape += parser.GetStringValue("shape", 0) + " ";
	            shape.resize(shape.size() - 1);
		        qr.makeSolidImage(r, g, b, (shape == "square") ? AnchorShape::Square : AnchorShape::Round);
		        qr.saveImage();
		    }
	    }

    }
	return 0;
}