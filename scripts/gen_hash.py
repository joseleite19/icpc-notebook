import subprocess

def run(cmd, inp = ""):
	return subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, input=inp.encode('utf-8')).stdout.decode('utf-8')

def get_hash(lines):
	code = '\n'.join(lines)
	out = run('cpp -dD -P -fpreprocessed | tr -d \'[:space:]\' | md5sum', code)
	return out.split()[0]
	print(out)
	return "qwe"

def process(content):

	pref = 'cpphash_'

	st = {}
	for i in range(len(content)):
		idx = content[i].rfind(pref)
		if idx == -1: continue

		key = content[i][idx:]
		key = key.split('_')[1]
		if key not in st:
			st[key] = i
		else:
			content[i] = content[i][:idx]
			content[i] += pref + key + ' '
			content[i] += get_hash(content[st[key]:i+1])


files = sorted(run("find code -type f -iname *.cpp").split())

for f in files:
	print('Processing {0}'.format(f))
	content = run("cat {0}".format(f))
	content = content.split('\n')
	old = content.copy()
	process(content)
	if content == old: continue
	run("cat > {0}".format(f), '\n'.join(content))
