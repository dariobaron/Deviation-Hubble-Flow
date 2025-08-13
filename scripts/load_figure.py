import pickle
import sys
import matplotlib.pyplot as plt

def loadPickledFigure(filename):
	try:
		with open(filename, 'rb') as file:
			data = pickle.load(file)
			return data
	except Exception as e:
		print(f"Error loading {filename}: {e}")
		sys.exit(1)

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print("Usage: python load_figure.py <pickle_file_path> [<pickle_file_path> ...]")
		sys.exit(1)

	figs = [loadPickledFigure(filename) for filename in sys.argv[1:]]
	for fig in figs:
		fig.show()
	input("Press return to exit...")