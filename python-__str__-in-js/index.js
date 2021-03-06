function print(...args) {
	const strings = args[0].slice(0)
	const objects = args.slice(1)
	if (objects.length > strings.length) {
		while (objects.length - strings.length) strings.push(null)
	}

	const output = []
	strings.forEach((arg, i) => {
		output.push(arg)
		if (objects[ i ]) {
			output.push(typeof objects[ i ] === 'function' 
				? objects[ i ].name
				: objects[ i ]
			)	
		}
	})

	this.log(...output)
}

console.print = print
console.print`hello`
console.print`hello ${Array.prototype.map}`

function func() {}

console.print`hello, this is a really long input string ${func}, ${String.prototype.split}`
