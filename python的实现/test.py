class Bloomfilter(object):

    def __init__(self, size):
        self.values = [False] * size
        self.size = size

    def hash_value(self, value):
        return hash(value) % self.size

    def add_value(self, value):
        h = self.hash_value(value)
        self.values[h] = True

    def might_contain(self, value):
        h = self.hash_value(value)
        return self.values[h]

    def print_contents(self):
        print(self.values)


bf = Bloomfilter(10)
bf.add_value('dog')
bf.add_value('fish')
bf.add_value('cat')
# bf.print_contents()
bf.add_value('bird')
# bf.print_contents()
# Note: contents are unchanged after adding bird - it collides
for term in ['dog', 'fish', 'cat', 'bird', 'duck', 'emu']:
    pass


# print(term)
# print(bf.hash_value(term))
# print(bf.might_contain(term))


def major_segments(s):
    major_breaks = ' '
    last = -1
    results = set()

    for idx, ch in enumerate(s):
        if ch in major_breaks:
            segment = s[last + 1:idx]
            results.add(segment)

            last = idx

    segment = s[last + 1:]
    results.add(segment)

    return results


def minor_segments(s):
    minor_breaks = '_.'
    last = -1
    results = set()

    for idx, ch in enumerate(s):
        if ch in minor_breaks:
            segment = s[last + 1:idx]
            results.add(segment)

            segment = s[:idx]
            results.add(segment)

            last = idx

    segment = s[last + 1:]
    results.add(segment)
    results.add(s)

    return results


def segments(event):
    results = set()
    for major in major_segments(event):
        for minor in minor_segments(major):
            results.add(minor)
    return results


# for term in segments('src_ip = 1.2.3.4'):
#     print(term)

class Splunk(object):
    def __init__(self):
        self.bf = Bloomfilter(64)
        self.terms = {}  # Dictionary of term to set of events
        self.events = []

    def add_event(self, event):
        event_id = len(self.events)
        self.events.append(event)
        for term in segments(event):
            self.bf.add_value(term)

            if term not in self.terms:
                self.terms[term] = set()
            self.terms[term].add(event_id)

    def search(self, term):
        if not self.bf.might_contain(term):
            return

        if term not in self.terms:
            return

        for event_id in sorted(self.terms[term]):
            yield self.events[event_id]


s = Splunk()
s.add_event('src_ip = 1.2.3.4')
s.add_event('src_ip = 5.6.7.8')
s.add_event('dst_ip = 1.2.3.4')


# for event in s.search('1.2.3.4'):
#     print(event)
# print('-' * 50)
# for event in s.search('src_ip'):
#     print(event)
# print('-' * 50)
# for event in s.search('ip'):
#     print(event)

class SplunkM(object):
    def __init__(self):
        self.bf = Bloomfilter(64)
        self.terms = {}  # Dictionary of term to set of events
        self.events = []

    def add_event(self, event):
        event_id = len(self.events)
        self.events.append(event)
        for term in segments(event):
            self.bf.add_value(term)
            if term not in self.terms:
                self.terms[term] = set()

            self.terms[term].add(event_id)

    def search_all(self, terms):
        results = set(range(len(self.events)))

        for term in terms:
            if not self.bf.might_contain(term):
                return
            if term not in self.terms:
                return

            results = results.intersection(self.terms[term])

        for event_id in sorted(results):
            yield self.events[event_id]

    def search_any(self, terms):
        results = set()

        for term in terms:
            if not self.bf.might_contain(term):
                continue
            if term not in self.terms:
                continue

            results = results.union(self.terms[term])

        for event_id in sorted(results):
            yield self.events[event_id]


s = SplunkM()
s.add_event('src_ip = 1.2.3.4')
s.add_event('src_ip = 5.6.7.8')
s.add_event('dst_ip = 1.2.3.4')

for event in s.search_all(['src_ip', '5.6']):
    print(event)
print('-' * 50)
for event in s.search_any(['src_ip', 'dst_ip']):
    print(event)
